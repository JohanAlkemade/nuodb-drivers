// Copyright 2012 NuoDB, Inc.
#include "./result.h"

#include <Connection.h>

node_db_nuodb::Result::Column::Column(ResultSetMetaData* metaData, int index) {
    this->binary = false;
    this->name = metaData->getColumnName(index);

    switch (metaData->getColumnType(index)) {
        case 1:
        case 2:
        case 3:
            this->type = STRING;
            break;
        case 4:
        case 5:
        case 6:
        case 17:
            this->type = INT;
            break;
        case 7:
        case 8:
            this->type = NUMBER;
            break;
        case 9:
            this->type = DATE;
            break;
        case 11:
            this->type = TIME;
            break;
        case 15:
        case 10:
            this->type = DATETIME;
            break;
        case 12:
        case 13:
        case 14:
        case 16:
            this->type = TEXT;
            this->binary = true;
            break;
        case 18:
            this->type = NUMBER;
            break;
        case 19:
            this->type = TEXT;
            break;
        case 20:
        case 21:
            this->type = TEXT;
            this->binary = true;
            break;
        case 22:
            this->type = BOOL;
            break;
        default:
            this->type = STRING;
            break;
    }
}

node_db_nuodb::Result::Column::~Column() {
}

bool node_db_nuodb::Result::Column::isBinary() const {
    return this->binary;
}

std::string node_db_nuodb::Result::Column::getName() const {
    return this->name;
}

node_db::Result::Column::type_t node_db_nuodb::Result::Column::getType() const {
    return this->type;
}

node_db_nuodb::Result::Result(nuodb::sqlapi::SqlStatement* statement) throw(node_db::Exception&)
    : columns(NULL),
    totalColumns(0),
    rowNumber(0),
    empty(true),
    statement(statement),
    resultSet(NULL),
    previousColumnLengths(NULL),
    previousRow(NULL),
    nextColumnLengths(NULL),
    nextRow(NULL) {

    try {
        try {
            this->statement->execute();
            this->resultSet = this->statement->getResultSet();
        } catch(SQLException& ex) {
            throw node_db::Exception(ex.getText());
        }

        if (this->resultSet != NULL) {
            ResultSetMetaData* metaData = this->resultSet->getMetaData();

            this->empty = false;
            this->totalColumns = metaData->getColumnCount();

            this->previousColumnLengths = new unsigned long[this->totalColumns];
            if (this->previousColumnLengths == NULL) {
                throw node_db::Exception("Could not create buffer for column lengths");
            }

            this->nextColumnLengths = new unsigned long[this->totalColumns];
            if (this->nextColumnLengths == NULL) {
                throw node_db::Exception("Could not create buffer for column lengths");
            }

            this->columns = new Column*[this->totalColumns];
            if (this->columns == NULL) {
                throw node_db::Exception("Could not allocate storage for columns");
            }

            for (uint16_t i = 0; i < this->totalColumns; i++) {
                this->columns[i] = new Column(metaData, i);
                if (this->columns[i] == NULL) {
                    this->totalColumns = i;
                    throw node_db::Exception("Could not allocate storage for column");
                }
            }

            this->nextRow = this->row(this->nextColumnLengths);
        }
    } catch(...) {
        this->free();
        throw;
    }
}

node_db_nuodb::Result::~Result() {
    this->free();
}

void node_db_nuodb::Result::free() throw() {
    this->release();

    this->freeRow(this->previousRow);
    this->freeRow(this->nextRow);

    if (this->previousColumnLengths != NULL) {
        delete [] this->previousColumnLengths;
    }

    if (this->nextColumnLengths != NULL) {
        delete [] this->nextColumnLengths;
    }

    if (this->columns != NULL) {
        for (uint16_t i = 0; i < this->totalColumns; i++) {
            delete this->columns[i];
        }
        delete [] this->columns;
    }
}

void node_db_nuodb::Result::release() throw() {
    if (this->resultSet != NULL) {
        this->resultSet->close();
        this->resultSet = NULL;
    }

    if (this->statement != NULL) {
        this->statement->close();
        this->statement = NULL;
    }
}

void node_db_nuodb::Result::freeRow(char** row) throw() {
    if (row != NULL) {
        for (uint16_t i = 0; i < this->totalColumns; i++) {
            delete [] row[i];
        }

        delete [] row;
    }
}

bool node_db_nuodb::Result::hasNext() const throw() {
    return (this->nextRow != NULL);
}

char** node_db_nuodb::Result::next() throw(node_db::Exception&) {
    this->freeRow(this->previousRow);

    if (this->nextRow == NULL) {
        return NULL;
    }

    this->rowNumber++;
    this->previousRow = this->nextRow;

    for(uint16_t i=0; i < this->totalColumns; i++) {
        this->previousColumnLengths[i] = this->nextColumnLengths[i];
    }
    this->nextRow = this->row(this->nextColumnLengths);

    return this->previousRow;
}

unsigned long* node_db_nuodb::Result::columnLengths() throw(node_db::Exception&) {
    return this->previousColumnLengths;
}

char** node_db_nuodb::Result::row(unsigned long* rowColumnLengths) throw(node_db::Exception&) {
    if (this->resultSet == NULL) {
        throw node_db::Exception("No ResultSet");
    } else if (!this->resultSet->next()) {
        return NULL;
    }

    uint16_t c=0;
    char** row;
    try {
        row = new char*[this->totalColumns];
        if (row == NULL) {
            throw node_db::Exception("Could not allocate buffer for row");
        }

        for (c=0; c < this->totalColumns; c++) {
            if (this->columns[c]->isBinary()) {
                ::Blob blob = this->resultSet->getBlob(c + 1);
                rowColumnLengths[c] = blob.length();

                row[c] = new char[rowColumnLengths[c]];
                if (row[c] == NULL) {
                    throw node_db::Exception("Could not allocate buffer for row column");
                }

                blob.read(rowColumnLengths[c], (unsigned char*) row[c], rowColumnLengths[c]);
            } else {
                std::string string;
                if (this->columns[c]->getType() == Column::DATETIME) {
                    nuodb::occi::Date date = this->resultSet->getDate(c + 1);
                    if (date.isNull()) {
                        rowColumnLengths[c] = 0;
                        row[c] = NULL;
                        continue;
                    }

                    string = date.toText("YYYY-MM-DD HH24:MI:SS");
                } else {
                    string = this->resultSet->getString(c + 1);
                }

                rowColumnLengths[c] = string.length();
                row[c] = new char[rowColumnLengths[c]];
                if (row[c] == NULL) {
                    throw node_db::Exception("Could not allocate buffer for row column");
                }

                memcpy(row[c], string.c_str(), rowColumnLengths[c]);
            }
        }
    } catch(...) {
        if (row != NULL) {
            for (uint16_t i=0; i < c; i++) {
                if (row[i] != NULL) {
                    delete [] row[i];
                }
            }
            delete [] row;
        }
        throw;
    }

    return row;
}

uint64_t node_db_nuodb::Result::index() const throw(std::out_of_range&) {
    if (this->rowNumber == 0) {
        throw std::out_of_range("Not standing on a row");
    }
    return (this->rowNumber - 1);
}

node_db_nuodb::Result::Column* node_db_nuodb::Result::column(uint16_t i) const throw(std::out_of_range&) {
    if (i >= this->totalColumns) {
        throw std::out_of_range("Wrong column index");
    }
    return this->columns[i];
}

uint64_t node_db_nuodb::Result::affectedCount() const throw() {
    return this->statement->getUpdateCount();
}

uint64_t node_db_nuodb::Result::insertId() const throw(node_db::Exception&) {
    //TODO:
    return 0;
}

uint16_t node_db_nuodb::Result::warningCount() const throw(node_db::Exception&) {
    //TODO:
    return 0;
}

uint16_t node_db_nuodb::Result::columnCount() const throw() {
    return this->totalColumns;
}

bool node_db_nuodb::Result::isBuffered() const throw() {
    return false;
}

bool node_db_nuodb::Result::isEmpty() const throw() {
    return this->empty;
}
