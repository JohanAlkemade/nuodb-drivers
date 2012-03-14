#pragma once

#include <msclr/marshal.h>

#include "nuodb/sqlapi/SqlColumnMetaData.h"
#include "nuodb/sqlapi/SqlConnection.h"
#include "nuodb/sqlapi/SqlDatabaseMetaData.h"
#include "nuodb/sqlapi/SqlEnvironment.h"
#include "nuodb/sqlapi/SqlExceptions.h"
#include "nuodb/sqlapi/SqlResultSet.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::ComponentModel;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Runtime::Serialization;
using namespace System::Security::Permissions;

#define NUODB_WRAPPER_BASE(T) \
	private: \
		nuodb::sqlapi::T& m_ref; \
	public: \
		T##Wrapper(nuodb::sqlapi::T& v) : m_ref(v) { } \
		~T##Wrapper() { m_ref.release(); } \
	public: \
		nuodb::sqlapi::T& ref() { return m_ref; }

namespace NuoDb
{
	class SqlEnvironmentWrapper
	{
		NUODB_WRAPPER_BASE(SqlEnvironment)
	};

	class SqlConnectionWrapper
	{
		NUODB_WRAPPER_BASE(SqlConnection)
	};

	class SqlResultSetWrapper
	{
		NUODB_WRAPPER_BASE(SqlResultSet)
	};

	class SqlColumnMetaDataWrapper
	{
		NUODB_WRAPPER_BASE(SqlColumnMetaData)
	};
}
