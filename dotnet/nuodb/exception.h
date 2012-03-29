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

#pragma once

namespace NuoDb
{
	/// NuoDb Error Codes
	public enum ErrorCode
	{
		NoSuchVersion = nuodb::sqlapi::NoSuchVersion,
		InternalError = nuodb::sqlapi::InternalError
	};

	/// <summary>
	/// The exception that is thrown when NuoDB returns a warning or error.
	/// This class cannot be inherited.
	/// </summary>
	[Serializable]
	public ref class NuoDbException sealed : public DbException
	{
#pragma region Instance Fields
	private:
		NuoDb::ErrorCode m_errorCode;
#pragma endregion

#pragma region Construction / Destruction
	public:
		/// <summary>
		/// Initializes a new instance of <see cref="NuoDbException"/>.
		/// </summary>
		NuoDbException() : m_errorCode(InternalError)
		{
		}

		/// <summary>
		/// Initializes a new instance of <see cref="NuoDbException"/>.
		/// </summary>
		/// <param name="message">The exception message.</param>
		NuoDbException(System::String^ message) :
			DbException(message),
			m_errorCode(InternalError)
		{
		}

		/// <summary>
		/// Initializes a new instance of <see cref="NuoDbException"/>.
		/// </summary>
		/// <param name="message">The exception message.</param>
		/// <param name="innerException">The Exception that caused this exception.</param>
		NuoDbException(System::String^ message, Exception^ innerException) :
			DbException(message, innerException),
			m_errorCode(InternalError)
		{
		}

	protected:
		[SecurityPermission(SecurityAction::Demand, SerializationFormatter = true)]
		NuoDbException(SerializationInfo^ info, StreamingContext context);

	internal:
		NuoDbException(nuodb::sqlapi::ErrorCodeException& e) :
			DbException(gcnew System::String(e.what())),
			m_errorCode((NuoDb::ErrorCode)e.errorCode())
		{
		}
#pragma endregion

#pragma region Properties
	public:
		virtual property NuoDb::ErrorCode ErrorCode
		{
			NuoDb::ErrorCode get() new { return m_errorCode; }
		}
#pragma endregion

#pragma region DbException Overrides
	public:
		/// <summary>
		/// Sets the <see cref="SerializationInfo"/> with information about the exception.
		/// </summary>
		/// <param name="info">The <see cref="SerializationInfo"/> that holds the serialized object data about the exception being thrown.</param>
		/// <param name="context">The <see cref="StreamingContext"/> that contains contextual information about the source or destination.</param>
		[SecurityPermission(SecurityAction::Demand, SerializationFormatter = true)]
		virtual void GetObjectData(SerializationInfo^ info, StreamingContext context) override;
#pragma endregion
	};
}
