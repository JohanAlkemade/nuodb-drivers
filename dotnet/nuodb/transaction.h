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
	ref class NuoDbConnection;

	/// Represents a NuoDb Database transaction.  This class cannot be inherited.
	public ref class NuoDbTransaction sealed : public DbTransaction
	{
#pragma region Instance Fields
	private:
		NuoDbConnection^ m_connection;
		System::Data::IsolationLevel m_isolationLevel;
#pragma endregion

#pragma region Construction / Destruction
	internal:
		NuoDbTransaction(NuoDbConnection^ connection, System::Data::IsolationLevel isolationLevel);
#pragma endregion

#pragma region Properties
	internal:
		/// <summary>
		/// The <see cref="NuoDbConnection"/> object associated with the transaction.
		/// </summary>
		property NuoDbConnection^ Connection
		{
			NuoDbConnection^ get() { return m_connection; }
		}
#pragma endregion

#pragma region DbTransaction Overrides
#pragma region Properties
	protected:
		/// <summary>
		/// The <see cref="DbConnection"/> object associated with the transaction.
		/// </summary>
		virtual property System::Data::Common::DbConnection^ DbConnection
		{
			System::Data::Common::DbConnection^ get() override;
		}

	public:
		/// <summary>
		/// Specifies the <see cref="IsolationLevel"/> for this transaction.
		/// </summary>
		virtual property System::Data::IsolationLevel IsolationLevel
		{
			System::Data::IsolationLevel get() override { return m_isolationLevel; }
		}
#pragma endregion

#pragma region Methods
	public:
		/// <summary>
		/// Commits the database transaction.
		/// </summary>
		virtual void Commit() override;

		/// <summary>
		/// Rolls back a transaction from a pending state.
		/// </summary>
		virtual void Rollback() override;
#pragma endregion
#pragma endregion
	};
}
