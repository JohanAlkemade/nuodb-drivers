/*
	Copyright (c) 2012, NuoDB, Inc.
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

		 * Redistributions of source code must retain the above copyright
			notice, this list of conditions and the following disclaimer.
		 * Redistributions in binary form must reproduce the above copyright
			notice, this list of conditions and the following disclaimer in the
			documentation and/or other materials provided with the distribution.
		 * Neither the name of NuoDB, Inc. nor the names of its contributors may
			be used to endorse or promote products derived from this software
			without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
	LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
	OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "stdafx.h"

#include "exception.h"
#include "connection.h"
#include "command.h"
#include "datareader.h"

#pragma region Construction / Destruction
NuoDb::NuoDbDataReader::NuoDbDataReader(SqlResultSetWrapper* results, NuoDbCommand^ command, System::Data::CommandBehavior behavior) :
	m_command(command),
	m_behavior(behavior),
	m_fieldCount(0),
	m_hasRows(false),
	m_isClosed(false),
	m_recordsAffected(-1),
	m_results(results)
{
	if (NULL == results)
		throw gcnew ArgumentNullException("results");

	if (nullptr == command)
		throw gcnew ArgumentNullException("command");

	if (nullptr == command->Connection)
		throw gcnew NuoDbException("The command has no connection.");

	if (!command->Connection->IsOpen)
		throw gcnew NuoDbException("The connection is not open.");
}

NuoDb::NuoDbDataReader::~NuoDbDataReader()
{
	Close();
}
#pragma endregion

#pragma region DbDataReader Overrides
#pragma region Properties
int NuoDb::NuoDbDataReader::Depth::get()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return 0;
}

int NuoDb::NuoDbDataReader::FieldCount::get()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return m_fieldCount;
}

bool NuoDb::NuoDbDataReader::HasRows::get()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return m_hasRows;
}

int NuoDb::NuoDbDataReader::RecordsAffected::get()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return m_recordsAffected;
}

int NuoDb::NuoDbDataReader::VisibleFieldCount::get()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return 0;
}

Object^ NuoDb::NuoDbDataReader::default::get(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Object^ NuoDb::NuoDbDataReader::default::get(System::String^ name)
{
	throw gcnew NotImplementedException();
}
#pragma endregion

#pragma region Methods
void NuoDb::NuoDbDataReader::Close()
{
	if (m_isClosed)
		return;

	delete m_results;

	m_results = NULL;

	if (CommandBehavior::CloseConnection == m_behavior)
		m_command->Connection->Close();

	m_isClosed = true;
}

bool NuoDb::NuoDbDataReader::GetBoolean(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

unsigned char NuoDb::NuoDbDataReader::GetByte(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

long long NuoDb::NuoDbDataReader::GetBytes(int ordinal, long long dataOffset, array<unsigned char>^ buffer, int bufferOffset, int length)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

wchar_t NuoDb::NuoDbDataReader::GetChar(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

long long NuoDb::NuoDbDataReader::GetChars(int ordinal, long long dataOffset, array<wchar_t>^ buffer, int bufferOffset, int length)
{
	throw gcnew NotImplementedException();
}

System::String^ NuoDb::NuoDbDataReader::GetDataTypeName(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

DateTime NuoDb::NuoDbDataReader::GetDateTime(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Decimal NuoDb::NuoDbDataReader::GetDecimal(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Double NuoDb::NuoDbDataReader::GetDouble(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

System::Collections::IEnumerator^ NuoDb::NuoDbDataReader::GetEnumerator()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Type^ NuoDb::NuoDbDataReader::GetFieldType(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Single NuoDb::NuoDbDataReader::GetFloat(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Guid NuoDb::NuoDbDataReader::GetGuid(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

short NuoDb::NuoDbDataReader::GetInt16(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

int NuoDb::NuoDbDataReader::GetInt32(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

long long NuoDb::NuoDbDataReader::GetInt64(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

System::String^ NuoDb::NuoDbDataReader::GetName(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

int NuoDb::NuoDbDataReader::GetOrdinal(System::String^ name)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Type^ NuoDb::NuoDbDataReader::GetProviderSpecificFieldType(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return DbDataReader::GetProviderSpecificFieldType(ordinal);
}

Object^ NuoDb::NuoDbDataReader::GetProviderSpecificValue(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return DbDataReader::GetProviderSpecificValue(ordinal);
}

int NuoDb::NuoDbDataReader::GetProviderSpecificValues(array<Object^>^ values)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	return DbDataReader::GetProviderSpecificValues(values);
}

DataTable^ NuoDb::NuoDbDataReader::GetSchemaTable()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

System::String^ NuoDb::NuoDbDataReader::GetString(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

Object^ NuoDb::NuoDbDataReader::GetValue(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

int NuoDb::NuoDbDataReader::GetValues(array<Object^>^ values)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

bool NuoDb::NuoDbDataReader::IsDBNull(int ordinal)
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

bool NuoDb::NuoDbDataReader::NextResult()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}

bool NuoDb::NuoDbDataReader::Read()
{
	if (m_isClosed)
		throw gcnew NuoDbException("The reader is closed.");

	throw gcnew NotImplementedException();
}
#pragma endregion
#pragma endregion
