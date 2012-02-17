// Copyright 2012 NuoDB, Inc.

#include <sstream>

#include "./connection.h"
#include "./result.h"

#include "nuodb/stdint.h"
#include "nuodb/sqlapi/SqlExceptions.h"
#include "nuodb/sqlapi/SqlEnvironment.h"
#include "nuodb/sqlapi/SqlPreparedStatement.h"
#include "nuodb/sqlapi/SqlDatabaseMetaData.h"

node_db_nuodb::Connection::Connection()
    : handle(0) {

    this->port = 48004;
    this->quoteName = '"';
}

class ConnectionHandle {
public:
    ConnectionHandle(nuodb::sqlapi::SqlEnvironment & environment, nuodb::sqlapi::SqlConnection & connection) : environment(environment), connection(connection) {}
    nuodb::sqlapi::SqlEnvironment & environment;
    nuodb::sqlapi::SqlConnection & connection;
};

node_db_nuodb::Connection::~Connection() {
    this->close();
}

bool node_db_nuodb::Connection::isAlive(bool ping) throw() {
    if (ping && this->alive) {
    }
    return this->alive;
}

void node_db_nuodb::Connection::open() throw(node_db::Exception&) {
    this->close();

    std::ostringstream conn_str;
    conn_str << this->database << "@" << this->hostname << ":" << this->port;

    try {
        nuodb::sqlapi::SqlOption options[3];
        options[0].option = "database"; options[0].extra = (void*) conn_str.str().c_str();
        options[1].option = "user"; options[1].extra = (void*) this->user.c_str();
        options[2].option = "password"; options[2].extra = (void*) this->password.c_str();

        nuodb::sqlapi::SqlOptionArray optionsArray;
        optionsArray.count = 3;
        optionsArray.array = options;

        using namespace nuodb::sqlapi;
        SqlEnvironment & environment = SqlEnvironment::createSqlEnvironment(&optionsArray);
        SqlConnection & connection = environment.createSqlConnection(&optionsArray);
        handle = reinterpret_cast<uintptr_t>(new ConnectionHandle(environment, connection));

        this->alive = true;
    } catch(nuodb::sqlapi::ErrorCodeException & exception) {
        throw node_db::Exception(exception.what());
    }
}

void node_db_nuodb::Connection::close() {
    if (this->alive) {
        ConnectionHandle * instance = reinterpret_cast<ConnectionHandle*>(handle);
        instance->connection.release();
        instance->environment.release();
        delete instance;
        handle = 0;
    }
    this->alive = false;
}

std::string node_db_nuodb::Connection::escape(const std::string& string) const throw(node_db::Exception&) {
    throw node_db::Exception("This binding does not implement escape()");
}

std::string node_db_nuodb::Connection::version() const {
    using namespace nuodb::sqlapi;
    ConnectionHandle * instance = reinterpret_cast<ConnectionHandle*>(handle);
    SqlDatabaseMetaData & metadata = instance->connection.getMetaData();
    std::string version = metadata.getDatabaseVersion();
    metadata.release();
    return version;
}

node_db::Result* node_db_nuodb::Connection::query(const std::string& query) const throw(node_db::Exception&) {
    ConnectionHandle * instance = reinterpret_cast<ConnectionHandle*>(handle);
    return new node_db_nuodb::Result(instance->connection.createPreparedStatement(query.c_str()));
}
