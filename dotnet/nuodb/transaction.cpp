#include "stdafx.h"

#include "connection.h"
#include "transaction.h"

#pragma region Construction / Destruction
NuoDb::NuoDbTransaction::NuoDbTransaction(NuoDbConnection^ connection, System::Data::IsolationLevel isolationLevel) :
	m_connection(nullptr),
	m_isolationLevel(isolationLevel)
{
	if (nullptr == connection)
		throw gcnew ArgumentNullException("connection");
}
#pragma endregion

#pragma region DbTransaction Overrides
#pragma region Properties
System::Data::Common::DbConnection^ NuoDb::NuoDbTransaction::DbConnection::get()
{
	return m_connection;
}
#pragma endregion

#pragma region Methods
void NuoDb::NuoDbTransaction::Commit()
{
	m_connection->CommitTransaction();
}

void NuoDb::NuoDbTransaction::Rollback()
{
	m_connection->RollbackTransaction();
}
#pragma endregion
#pragma endregion
