// Copyright 2012 NuoDB, Inc.
#include "./connection.h"

node_db_nuodb::Connection::Connection()
    : environment(NULL),
      connection(NULL) {
    this->port = 1521;
    this->quoteName = '"';
}

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

    try {
        this->connection = createConnection();
        Properties *properties = connection->allocProperties();
        properties->putValue("user", this->user.c_str());
        properties->putValue("password", this->password.c_str());
        properties->putValue("schema", database.c_str());
        connection->openDatabase(this->database.c_str(), properties);
        this->alive = true;
    } catch(SQLException& exception) {
        throw node_db::Exception(exception.getText());
    }
}

void node_db_nuodb::Connection::close() {
    if (this->alive) {
        this->connection->close();
    }
    this->alive = false;
}

std::string node_db_nuodb::Connection::escape(const std::string& string) const throw(node_db::Exception&) {
    throw node_db::Exception("This binding does not implement escape()");
}

std::string node_db_nuodb::Connection::version() const {
    return this->connection->getMetaData()->getDatabaseProductVersion();
}

node_db::Result* node_db_nuodb::Connection::query(const std::string& query) const throw(node_db::Exception&) {
    return new node_db_nuodb::Result(this->connection->prepareStatement(query.c_str()));
}
