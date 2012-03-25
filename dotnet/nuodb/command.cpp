#include "stdafx.h"

#include "connection.h"
#include "transaction.h"
#include "exception.h"
#include "parameter.h"
#include "command.h"

#pragma region Construction / Destruction
NuoDb::NuoDbCommand::NuoDbCommand() :
	m_commandText(System::String::Empty),
	m_commandTimeout(NUODB_DEFAULT_COMMAND_TIMEOUT),
	m_commandType(System::Data::CommandType::Text),
	m_connection(nullptr),
	m_parameters(gcnew NuoDbParameterCollection()),
	m_transaction(nullptr),
	m_designTimeVisible(false),
	m_updateRowSource(System::Data::UpdateRowSource::None)
{
}
#pragma endregion 

#pragma region Properties
void NuoDb::NuoDbCommand::Connection::set(NuoDb::NuoDbConnection^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	m_connection = value;
}

void NuoDb::NuoDbCommand::Transaction::set(NuoDbTransaction^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	m_transaction = value;
	m_connection = value->Connection;
}
#pragma endregion 

#pragma region Methods
NuoDb::NuoDbDataReader^ NuoDb::NuoDbCommand::ExecuteDataReader(CommandBehavior behavior)
{
	throw gcnew NotImplementedException();
}
#pragma endregion

#pragma region DbCommand Overrides
#pragma region Properties
void NuoDb::NuoDbCommand::CommandText::set(System::String^ value)
{
	if (System::String::IsNullOrEmpty(value))
		throw gcnew ArgumentNullException("value");

	m_commandText = value;
}

void NuoDb::NuoDbCommand::CommandType::set(System::Data::CommandType value)
{
	if (value != System::Data::CommandType::Text)
		throw gcnew NotSupportedException("Only CommandType.Text is supported");

	m_commandType = value;
}

System::Data::Common::DbConnection^ NuoDb::NuoDbCommand::DbConnection::get()
{
	return m_connection;
}

void NuoDb::NuoDbCommand::DbConnection::set(System::Data::Common::DbConnection^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbConnection^ p = dynamic_cast<NuoDbConnection^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbConnection.");

	m_connection = p;
}

System::Data::Common::DbParameterCollection^ NuoDb::NuoDbCommand::DbParameterCollection::get()
{
	return m_parameters;
}

System::Data::Common::DbTransaction^ NuoDb::NuoDbCommand::DbTransaction::get()
{
	return m_transaction;
}

void NuoDb::NuoDbCommand::DbTransaction::set(System::Data::Common::DbTransaction^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbTransaction^ p = dynamic_cast<NuoDbTransaction^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbTransaction.");

	m_transaction = p;
	m_connection = p->Connection;
}
#pragma endregion

#pragma region Methods
void NuoDb::NuoDbCommand::Cancel()
{
	throw gcnew NotSupportedException();
}

NuoDb::NuoDbParameter^ NuoDb::NuoDbCommand::CreateParameter()
{
	return gcnew NuoDbParameter();
}

DbParameter^ NuoDb::NuoDbCommand::CreateDbParameter()
{
	return gcnew NuoDbParameter();
}

DbDataReader^ NuoDb::NuoDbCommand::ExecuteDbDataReader(CommandBehavior behavior)
{
	if (nullptr == m_connection)
		throw gcnew NuoDbException("No connection has been associated with the command.");

	return ExecuteReader(behavior);
}

int NuoDb::NuoDbCommand::ExecuteNonQuery()
{
	if (nullptr == m_connection)
		throw gcnew NuoDbException("No connection has been associated with the command.");

	throw gcnew NotImplementedException();
}

Object^ NuoDb::NuoDbCommand::ExecuteScalar()
{
	if (nullptr == m_connection)
		throw gcnew NuoDbException("No connection has been associated with the command.");

	throw gcnew NotImplementedException();
}

void NuoDb::NuoDbCommand::Prepare()
{
	if (nullptr == m_connection)
		throw gcnew NuoDbException("No connection has been associated with the command.");

	throw gcnew NotImplementedException();
}
#pragma endregion
#pragma endregion
