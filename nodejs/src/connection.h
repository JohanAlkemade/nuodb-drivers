// Copyright 2012 NuoDB, Inc.
#ifndef NODE_DB_NUODB_CONNECTION_H_
#define NODE_DB_NUODB_CONNECTION_H_

#include <string>
#include <sstream>
#include "./node-db/connection.h"

#include "nuodb/sqlapi/SqlConnection.h"

namespace node_db_nuodb {
    class Connection : public node_db::Connection {
        public:
            Connection();
            ~Connection();
            bool isAlive(bool ping) throw();
            void open() throw(node_db::Exception&);
            void close();
            std::string escape(const std::string& string) const throw(node_db::Exception&);
            std::string version() const;
            node_db::Result* query(const std::string& query) const throw(node_db::Exception&);
        private:
            uintptr_t handle;
    };
}

#endif  /* NODE_DB_NUODB_CONNECTION_H_ */
