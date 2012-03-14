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
