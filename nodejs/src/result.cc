// Copyright 2012 NuoDB, Inc.
#include "./result.h"

#include "nuodb/sqlapi/SqlDate.h"

node_db_nuodb::Result::Column::Column(nuodb::sqlapi::SqlColumnMetaData & metaData) {
    this->binary = false;

    using namespace nuodb::sqlapi;
    switch (metaData.getType()) {
        case SQL_DOUBLE:
            this->type = NUMBER;
            break;
        case SQL_INTEGER:
            this->type = INT;
            break;
        case SQL_DATE:
        case SQL_TIME:
        case SQL_DATETIME:
            this->type = DATETIME;
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

node_db_nuodb::Result::Result(nuodb::sqlapi::SqlResultSet & results) throw(node_db::Exception&)
    : columns(NULL),
    totalColumns(0),
    rowNumber(0),
    empty(true),
    resultSet(results),
    previousColumnLengths(NULL),
    previousRow(NULL),
    nextColumnLengths(NULL),
    nextRow(NULL) {

    using namespace nuodb::sqlapi;
    try {
        this->empty = false;
        this->totalColumns = resultSet.getColumnCount();

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
            SqlColumnMetaData & metaData = this->resultSet.getMetaData(i);
            this->columns[i] = new Column(metaData);
            if (this->columns[i] == NULL) {
                this->totalColumns = i;
                throw node_db::Exception("Could not allocate storage for column");
            }
            metaData.release();
        }

        this->nextRow = this->row(this->nextColumnLengths);
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
    this->resultSet.release();
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

#define Get_year(od) (((od)->century - 100) * 100 + ((od)->year - 100))
#define Get_month(od) ((od)->month)
#define Get_day(od) ((od)->day)
#define Get_hour(od) ((od)->hour - 1)
#define Get_minute(od) ((od)->minute - 1)
#define Get_second(od) ((od)->second - 1)

char** node_db_nuodb::Result::row(unsigned long* rowColumnLengths) throw(node_db::Exception&) {
    if (!this->resultSet.next()) {
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
            std::string string;
            if (this->columns[c]->getType() == Column::DATETIME) {
                nuodb::sqlapi::SqlDate const * date = this->resultSet.getDate(c + 1);
                if (date == NULL) {
                    rowColumnLengths[c] = 0;
                    row[c] = NULL;
                    continue;
                }

                time_t when = (time_t) date->getTime();
                tm * time = gmtime(&when);

                char buffer [80];
                strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time);

                string = buffer;
            } else {
                string = this->resultSet.getString(c + 1);
            }

            rowColumnLengths[c] = string.length();
            row[c] = new char[rowColumnLengths[c]];
            if (row[c] == NULL) {
                throw node_db::Exception("Could not allocate buffer for row column");
            }

            memcpy(row[c], string.c_str(), rowColumnLengths[c]);
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
    return 0; // not possible without restreaming an entirely new result set across the network
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
