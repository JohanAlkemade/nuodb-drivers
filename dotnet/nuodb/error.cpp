#include "stdafx.h"

#include "error.h"

#pragma region NuoDbError
#pragma region Construction / Destruction
NuoDb::NuoDbError::NuoDbError(String^ server, String^ message, int lineNumber, int number, Byte^ state) :
	m_source(".Net NuoDb Data Provider"),
	m_server(server),
	m_message(message),
	m_lineNumber(lineNumber),
	m_number(number),
	m_state(state)
{
}
#pragma endregion
#pragma endregion

#pragma region NuoDbErrorCollection
#pragma region Construction / Destruction
NuoDb::NuoDbErrorCollection::NuoDbErrorCollection()
{
	m_errors = gcnew List<NuoDbError^>();
}
#pragma endregion

#pragma region Properties
NuoDb::NuoDbError^ NuoDb::NuoDbErrorCollection::default::get(int index)
{
	if (index < 0 || index >= m_errors->Count)
		throw gcnew IndexOutOfRangeException("index");

	return m_errors[index];
}
#pragma endregion

#pragma region Methods
void NuoDb::NuoDbErrorCollection::Add(NuoDb::NuoDbError^ e)
{
	if (nullptr == e)
		throw gcnew ArgumentNullException("e");

	m_errors->Add(e);
}

void NuoDb::NuoDbErrorCollection::CopyTo(array<NuoDb::NuoDbError^>^ a, int index)
{
	if (nullptr == a)
		throw gcnew ArgumentNullException("a");

	if (index < 0 || index >= a->Length)
		throw gcnew IndexOutOfRangeException("index");

	m_errors->CopyTo(a, index);
}
#pragma endregion

#pragma region ICollection Implementation
void NuoDb::NuoDbErrorCollection::CopyTo(Array^ a, int index)
{
	if (nullptr == a)
		throw gcnew ArgumentNullException("a");

	if (index < 0 || index >= a->Length)
		throw gcnew IndexOutOfRangeException("index");

	Array::Copy((Array^)m_errors, a, index);
}
#pragma endregion
#pragma endregion
