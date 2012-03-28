#ifndef PHP_PDO_NUODB_CPP_INT_H
#define PHP_PDO_NUODB_CPP_INT_H

#include <nuodb/sqlapi/SqlConnection.h>
#include <nuodb/sqlapi/SqlEnvironment.h>
#include <nuodb/sqlapi/SqlConnection.h>
#include <nuodb/sqlapi/SqlDatabaseMetaData.h>
#include <nuodb/sqlapi/SqlStatement.h>
#include <nuodb/sqlapi/SqlExceptions.h>

using namespace nuodb::sqlapi;

class NuoDbConnection {
 private:
	SqlOptionArray *_options;
	SqlEnvironment *_env;
	SqlConnection *_con;
 public:
	NuoDbConnection(SqlOptionArray *options) {
		_options = options;
		_env = NULL;
		_con = NULL;
	}
	~NuoDbConnection() {
		if (_con == NULL) {
			delete _con;
			_con = NULL;
		}
		if (_env == NULL) {
			delete _env;
			_env = NULL;
		}
	}
	int initialize() {
		int rval = 0;
		try {
			_env = SqlEnvironment::createSqlEnvironment(_options);
            _con = _env->createSqlConnection(_options);
        }
        catch (ErrorCodeException & e) {
			rval = (int) e.errorCode();
        }
		return rval;
	}
	
	SqlStatement *createStatement() {
		if (_con == NULL) return NULL;
		return _con->createStatement();
	}
};

class NuoSqlStatement {
 private: 
	SqlStatement *_stmt;
	NuoDbConnection *_nuoDbCon;
 public:
	NuoSqlStatement(NuoDbConnection *nuoDbCon) {
		_nuoDbCon = nuoDbCon;
		_stmt = _nuoDbCon->createStatement();
	}	
};

#endif	/* PHP_PDO_NUODB_INT_CPP_H */
