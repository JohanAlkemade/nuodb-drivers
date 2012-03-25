#include "stdafx.h"

#include "exception.h"

NuoDb::NuoDbException::NuoDbException(SerializationInfo^ info, StreamingContext context) : DbException(info, context)
{
	if (nullptr == info)
		throw gcnew ArgumentNullException("info");

	info->AddValue("ErrorCode", (int)m_errorCode);
}

void NuoDb::NuoDbException::GetObjectData(SerializationInfo^ info, StreamingContext context)
{
	if (nullptr == info)
		throw gcnew ArgumentNullException("info");

	DbException::GetObjectData(info, context);

	m_errorCode = (NuoDb::ErrorCode)info->GetInt32("ErrorCode");
}
