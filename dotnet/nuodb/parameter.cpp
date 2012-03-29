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

#include "parameter.h"

#pragma region NuoDbParameter
#pragma region Construction / Destruction
NuoDb::NuoDbParameter::NuoDbParameter() : 
	m_dbType(String),
	m_direction(ParameterDirection::Input),
	m_nullable(true),
	m_name(System::String::Empty),
	m_size(0),
	m_source(System::String::Empty),
	m_sourceNullMapping(false),
	m_version(DataRowVersion::Original),
	m_value(nullptr)
{
}
#pragma endregion

#pragma region Properties
void NuoDb::NuoDbParameter::NuoDbType::set(NuoDb::NuoDbType t)
{
	m_dbType = t;
	m_version = DataRowVersion::Current;
}
#pragma endregion

#pragma region DbParameter Overrides
#pragma region Properties
System::Data::DbType NuoDb::NuoDbParameter::DbType::get()
{
	switch (m_dbType)
	{
		case Boolean: return System::Data::DbType::Boolean;
		case Integer: return System::Data::DbType::Int32;
		case BigInt: return System::Data::DbType::Int64;
		case Double: return System::Data::DbType::Double;
		case Date: return System::Data::DbType::Date;
		case Time: return System::Data::DbType::Time;
		case DateTime: return System::Data::DbType::DateTime;

		default: return System::Data::DbType::String;
	}
}

void NuoDb::NuoDbParameter::DbType::set(System::Data::DbType value)
{
	switch (value)
	{
		case System::Data::DbType::Boolean: m_dbType = Boolean; break;
		case System::Data::DbType::Int32: m_dbType = Integer; break;
		case System::Data::DbType::Int64: m_dbType = BigInt; break;
		case System::Data::DbType::Double: m_dbType = Double; break;
		case System::Data::DbType::String: m_dbType = String; break;
		case System::Data::DbType::Date: m_dbType = Date; break;
		case System::Data::DbType::Time: m_dbType = Time; break;
		case System::Data::DbType::DateTime: m_dbType = DateTime; break;

		default: throw gcnew ArgumentException("value");
	}

	m_version = DataRowVersion::Current;
}

void NuoDb::NuoDbParameter::ParameterName::set(System::String^ value)
{
	if (System::String::IsNullOrEmpty(value))
		throw gcnew ArgumentNullException("ParameterName");

	m_name = value;
}

void NuoDb::NuoDbParameter::Value::set(Object^ value)
{
	m_version = DataRowVersion::Current;
	m_value = value;
}
#pragma endregion

#pragma region Methods
void NuoDb::NuoDbParameter::ResetDbType()
{
	m_version = DataRowVersion::Current;
	m_dbType = String;
}
#pragma endregion
#pragma endregion
#pragma endregion

#pragma region NuoDbParameterCollection
#pragma region Construction / Destruction
NuoDb::NuoDbParameterCollection::NuoDbParameterCollection()
{
	m_parameters = gcnew List<NuoDbParameter^>();
}
#pragma endregion

#pragma region Methods
NuoDb::NuoDbParameter^ NuoDb::NuoDbParameterCollection::Add(System::String^ parameterName, NuoDb::NuoDbType type)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	if (IndexOf(parameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + parameterName+ "\" in the collection", "value");

	NuoDbParameter^ p = gcnew NuoDbParameter();

	p->ParameterName = parameterName;
	p->NuoDbType = type;

	m_parameters->Add(p);

	return p;
}

NuoDb::NuoDbParameter^ NuoDb::NuoDbParameterCollection::Add(System::String^ parameterName, NuoDbType type, int size)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	if (IndexOf(parameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + parameterName + "\" in the collection", "value");

	NuoDbParameter^ p = gcnew NuoDbParameter();

	p->ParameterName = parameterName;
	p->NuoDbType = type;
	p->Size = size;

	m_parameters->Add(p);

	return p;
}

NuoDb::NuoDbParameter^ NuoDb::NuoDbParameterCollection::Add(System::String^ parameterName, NuoDbType type, int size, System::String^ sourceColumn)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	if (IndexOf(parameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + parameterName + "\" in the collection", "value");

	if (System::String::IsNullOrEmpty(sourceColumn))
		throw gcnew ArgumentNullException("sourceColumn");

	NuoDbParameter^ p = gcnew NuoDbParameter();

	p->ParameterName = parameterName;
	p->NuoDbType = type;
	p->Size = size;
	p->SourceColumn = sourceColumn;

	m_parameters->Add(p);

	return p;
}

void NuoDb::NuoDbParameterCollection::AddRange(array<NuoDbParameter^>^ values)
{
	if (nullptr == values)
		throw gcnew ArgumentNullException("values");

	for each (NuoDbParameter^ p in values)
	{
		if (System::String::IsNullOrEmpty(p->ParameterName))
			throw gcnew ArgumentException("At least one parameter does not have a name.");

		if (IndexOf(p->ParameterName) >= 0)
			throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

		m_parameters->Add(p);
	}
}

void NuoDb::NuoDbParameterCollection::CopyTo(array<NuoDbParameter^>^ a, int index)
{
	if (nullptr == a)
		throw gcnew ArgumentNullException("a");

	m_parameters->CopyTo(a, index);
}

void NuoDb::NuoDbParameterCollection::Insert(int index, NuoDbParameter^ value)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	if (IndexOf(value->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + value->ParameterName + "\" in the collection", "value");

	m_parameters->Insert(index, value);
}

void NuoDb::NuoDbParameterCollection::Remove(NuoDbParameter^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	m_parameters->Remove(value);
}
#pragma endregion

#pragma region DbParameterCollection Overrides
#pragma region Properties
NuoDb::NuoDbParameter^ NuoDb::NuoDbParameterCollection::default::get(int index)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	return m_parameters[index];
}

void NuoDb::NuoDbParameterCollection::default::set(int index, NuoDbParameter^ value)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	if (System::String::IsNullOrEmpty(value->ParameterName))
		throw gcnew ArgumentException("The parameter does not have a name.");

	if (IndexOf(value->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + value->ParameterName + "\" in the collection", "value");

	m_parameters[index] = value;
}

NuoDb::NuoDbParameter^ NuoDb::NuoDbParameterCollection::default::get(System::String^ parameterName)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	int index = IndexOf(parameterName);

	if (index < 0)
		throw gcnew IndexOutOfRangeException("parameterName");

	return m_parameters[index];
}

void NuoDb::NuoDbParameterCollection::default::set(System::String^ parameterName, NuoDbParameter^ value)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	int index = IndexOf(parameterName);

	if (index < 0)
		throw gcnew IndexOutOfRangeException("parameterName");

	if (System::String::IsNullOrEmpty(value->ParameterName))
		throw gcnew ArgumentException("The parameter does not have a name.");

	if (value->ParameterName != parameterName && IndexOf(value->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + value->ParameterName + "\" in the collection", "value");

	m_parameters[index] = value;
}
#pragma endregion

#pragma region Methods
int NuoDb::NuoDbParameterCollection::Add(Object^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbParameter^ p = dynamic_cast<NuoDbParameter^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbParameter", "value");

	if (System::String::IsNullOrEmpty(p->ParameterName))
		throw gcnew ArgumentException("The parameter does not have a name.");

	if (IndexOf(p->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

	m_parameters->Add(p);

	return m_parameters->Count - 1;
}

void NuoDb::NuoDbParameterCollection::AddRange(Array^ values)
{
	if (nullptr == values)
		throw gcnew ArgumentNullException("values");

	for each (Object^ o in values)
	{
		NuoDbParameter^ p = dynamic_cast<NuoDbParameter^>(o);

		if (nullptr == p)
			throw gcnew ArgumentException("At least one object in the array is not a NuoDbParameter", "values");

		if (System::String::IsNullOrEmpty(p->ParameterName))
			throw gcnew ArgumentException("At least one parameter does not have a name.");

		if (IndexOf(p->ParameterName) >= 0)
			throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

		m_parameters->Add(p);
	}
}

bool NuoDb::NuoDbParameterCollection::Contains(Object^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	if (0 == m_parameters->Count)
		return false;

	for each (NuoDbParameter^ p in m_parameters)
		if (value == p->Value)
			return true;

	return false;
}

bool NuoDb::NuoDbParameterCollection::Contains(System::String^ value)
{
	if (System::String::IsNullOrEmpty(value))
		throw gcnew ArgumentNullException("value");

	return IndexOf(value) >= 0;
}

void NuoDb::NuoDbParameterCollection::CopyTo(Array^ a, int index)
{
	if (nullptr == a)
		throw gcnew ArgumentNullException("a");

	Array::Copy((Array^)m_parameters, a, index);
}

int NuoDb::NuoDbParameterCollection::IndexOf(Object^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	for (int i = 0; i < m_parameters->Count; i++)
		if (m_parameters == value)
			return i;

	return -1;
}

int NuoDb::NuoDbParameterCollection::IndexOf(System::String^ parameterName)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	for (int i = 0; i < m_parameters->Count; i++)
		if (m_parameters[i]->ParameterName == parameterName)
			return i;

	return -1;
}

void NuoDb::NuoDbParameterCollection::Insert(int index, Object^ value)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbParameter^ p = dynamic_cast<NuoDbParameter^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbParameter", "value");

	if (System::String::IsNullOrEmpty(p->ParameterName))
		throw gcnew ArgumentException("The parameter does not have a name.");

	if (IndexOf(p->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

	m_parameters->Insert(index, p);
}

void NuoDb::NuoDbParameterCollection::Remove(Object^ value)
{
	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	int index = IndexOf(value);

	if (index >= 0)
		m_parameters->RemoveAt(index);
}

void NuoDb::NuoDbParameterCollection::RemoveAt(int index)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	m_parameters->RemoveAt(index);
}

void NuoDb::NuoDbParameterCollection::RemoveAt(System::String^ parameterName)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	int index = IndexOf(parameterName);

	if (index >= 0)
		m_parameters->RemoveAt(index);
	else
		throw gcnew IndexOutOfRangeException("parameterName");
}

void NuoDb::NuoDbParameterCollection::SetParameter(int index, DbParameter^ value)
{
	if (index < 0 || index >= m_parameters->Count)
		throw gcnew IndexOutOfRangeException("index");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbParameter^ p = dynamic_cast<NuoDbParameter^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbParameter", "value");

	if (IndexOf(p->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

	m_parameters[index] = p;
}

void NuoDb::NuoDbParameterCollection::SetParameter(System::String^ parameterName, DbParameter^ value)
{
	if (System::String::IsNullOrEmpty(parameterName))
		throw gcnew ArgumentNullException("parameterName");

	if (nullptr == value)
		throw gcnew ArgumentNullException("value");

	NuoDbParameter^ p = dynamic_cast<NuoDbParameter^>(value);

	if (nullptr == p)
		throw gcnew ArgumentException("value is not a NuoDbParameter", "value");

	int index = IndexOf(parameterName);

	if (index < 0)
		throw gcnew IndexOutOfRangeException("parameterName");

	if (System::String::IsNullOrEmpty(p->ParameterName))
		throw gcnew ArgumentException("The parameter does not have a name.");

	if (p->ParameterName != parameterName && IndexOf(p->ParameterName) >= 0)
		throw gcnew ArgumentException("There is already a parameter named \"" + p->ParameterName + "\" in the collection", "value");

	m_parameters[index] = p;
}
#pragma endregion
#pragma endregion
#pragma endregion
