// Copyright 2012 NuoDB, Inc.
#ifndef SRC_RESULT_H_
#define SRC_RESULT_H_

#include <cstring>
#include <string>
#include <stdexcept>

#include "./node-db/exception.h"
#include "./node-db/result.h"

#include "nuodb/sqlapi/SqlResultSet.h"
#include "nuodb/sqlapi/SqlMetaData.h"

namespace node_db_nuodb {
class Result : public node_db::Result {
    public:
        class Column : public node_db::Result::Column {
            public:
                explicit Column(nuodb::sqlapi::SqlMetaData & metaData);
                ~Column();
                bool isBinary() const;
                std::string getName() const;
                node_db::Result::Column::type_t getType() const;

            protected:
                std::string name;
                type_t type;
                bool binary;
        };

        explicit Result(nuodb::sqlapi::SqlResultSet & results) throw(node_db::Exception&);
        ~Result();
        void release() throw();
        bool hasNext() const throw();
        char** next() throw(node_db::Exception&);
        unsigned long* columnLengths() throw(node_db::Exception&);
        uint64_t index() const throw(std::out_of_range&);
        Column* column(uint16_t i) const throw(std::out_of_range&);
        uint16_t columnCount() const throw();
        uint64_t affectedCount() const throw();
        uint64_t insertId() const throw(node_db::Exception&);
        uint16_t warningCount() const throw(node_db::Exception&);
        bool isBuffered() const throw();
        bool isEmpty() const throw();

    protected:
        Column** columns;
        uint16_t totalColumns;
        uint64_t rowNumber;
        bool empty;

        char** row(unsigned long* rowColumnLengths) throw(node_db::Exception&);
        void free() throw();

    private:
        nuodb::sqlapi::SqlResultSet & resultSet;
        unsigned long* previousColumnLengths;
        char** previousRow;
        unsigned long* nextColumnLengths;
        char** nextRow;

        void freeRow(char** row) throw();
};
}

#endif  // SRC_RESULT_H_
