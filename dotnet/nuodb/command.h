#pragma once

#define NUODB_DEFAULT_COMMAND_TIMEOUT 60

namespace NuoDb
{
	ref class NuoDbConnection;
	ref class NuoDbDataReader;
	ref class NuoDbParameter;
	ref class NuoDbParameterCollection;
	ref class NuoDbTransaction;

	public ref class NuoDbCommand sealed : public DbCommand
	{
#pragma region Instance Fields
	private:
		System::String^ m_commandText;
		int m_commandTimeout;
		System::Data::CommandType m_commandType;
		NuoDbConnection^ m_connection;
		NuoDbParameterCollection^ m_parameters;
		NuoDbTransaction^ m_transaction;
		bool m_designTimeVisible;
		System::Data::UpdateRowSource m_updateRowSource;
#pragma endregion 

#pragma region Construction / Destruction
	public:
		NuoDbCommand();
#pragma endregion

#pragma region Properties
	public:
		/// <summary>
		/// Gets or sets the <see cref="NuoDb::NuoDbConnection"/> used by this <see cref="NuoDbCommand"/>.
		/// </summary>
		property NuoDb::NuoDbConnection^ Connection
		{
			NuoDb::NuoDbConnection^ get() { return m_connection; }
			void set(NuoDb::NuoDbConnection^ value);
		}

		/// <summary>
		/// Gets the collection of <see cref="NuoDbParameter"/> objects.
		/// </summary>
		property NuoDbParameterCollection^ Parameters
		{
			NuoDbParameterCollection^ get() { return m_parameters; }
		}

		/// <summary>
		/// Gets or sets the <see cref="NuoDbTransaction"/> within which this <see cref="NuoDbCommand"/> object executes.
		/// </summary>
		property NuoDbTransaction^ Transaction
		{
			NuoDbTransaction^ get() { return m_transaction; }
			void set(NuoDbTransaction^ value);
		}
#pragma endregion

#pragma region Methods
	public:
		/// <summary>
		/// Executes the command text against the connection.
		/// </summary>
		/// <param name="behavior">An instance of <see cref="CommandBehavior"/>.</param>
		/// <returns>A <see cref="NuoDbDataReader"/>.</returns>
		NuoDbDataReader^ ExecuteDataReader(CommandBehavior behavior);
#pragma endregion

#pragma region DbCommand Overrides
#pragma region Properties
	public:
		/// <summary>
		/// Gets or sets the text command to run against the data source.
		/// </summary>
		virtual property System::String^ CommandText
		{
			System::String^ get() override { return m_commandText; }
			void set(System::String^ value) override;
		}

		/// <summary>
		/// Gets or sets the wait time in seconds before terminating the attempt to execute a command and generating an error.
		/// </summary>
		virtual property int CommandTimeout
		{
			int get() override { return m_commandTimeout; }
			void set(int value) override { m_commandTimeout = value; }
		}

		/// <summary>
		/// Indicates or specifies how the <see cref="CommandText"/> property is interpreted.
		/// </summary>
		virtual property System::Data::CommandType CommandType
		{
			System::Data::CommandType get() override { return m_commandType; }
			void set(System::Data::CommandType value) override;
		}

		/// <summary>
		/// Gets or sets the <see cref="DbConnection"/> used by this <see cref="NuoDbCommand"/>.
		/// </summary>
		virtual property System::Data::Common::DbConnection^ DbConnection
		{
			System::Data::Common::DbConnection^ get() override;
			void set(System::Data::Common::DbConnection^ value) override;
		}

		/// <summary>
		/// Gets the collection of <see cref="DbParameter"/> objects.
		/// </summary>
		virtual property System::Data::Common::DbParameterCollection^ DbParameterCollection
		{
			System::Data::Common::DbParameterCollection^ get() override;
		}

		/// <summary>
		/// Gets or sets the <see cref="DbTransaction"/> within which this <see cref="NuoDbCommand"/> object executes.
		/// </summary>
		virtual property System::Data::Common::DbTransaction^ DbTransaction
		{
			System::Data::Common::DbTransaction^ get() override;
			void set(System::Data::Common::DbTransaction^ value) override;
		}

		/// <summary>
		/// Gets or sets a value indicating whether the command object should be visible
		/// in a customized interface control.
		/// </summary>
		virtual property bool DesignTimeVisible
		{
			bool get() override { return m_designTimeVisible; }
			void set(bool value) override { m_designTimeVisible = value; }
		}

		/// <summary>
		/// Gets or sets how command results are applied to the <see cref="DataRow"/>
		/// when used by the Update method of a <see cref="DbDataAdapter"/>.
		/// </summary>
		virtual property System::Data::UpdateRowSource UpdatedRowSource
		{
			System::Data::UpdateRowSource get() override { return m_updateRowSource; }
			void set(System::Data::UpdateRowSource value) override { m_updateRowSource = value; }
		}
#pragma endregion

#pragma region Methods
	public:
		/// <summary>
		/// Attempts to cancels the execution of a <see cref="NuoDbCommand"/>.
		/// </summary>
		virtual void Cancel() override;

		/// <summary>
		/// Creates a new instance of a <see cref="NuoDbParameter"/>.
		/// </summary>
		/// <returns>A new instance of a <see cref="NuoDbParameter"/></returns>
		virtual NuoDbParameter^ CreateParameter() new;

		/// <summary>
		/// Creates a new instance of a <see cref="NuoDbCommand"/>.
		/// </summary>
		/// <returns>A new instance of a <see cref="NuoDbCommand"/></returns>
		virtual DbParameter^ CreateDbParameter() override;

		/// <summary>
		/// Executes the command text against the connection.
		/// </summary>
		/// <param name="behavior">An instance of <see cref="CommandBehavior"/>.</param>
		/// <returns>A <see cref="DbDataReader"/>.</returns>
		virtual DbDataReader^ ExecuteDbDataReader(CommandBehavior behavior) override;

		/// <summary>
		/// Executes a SQL statement against a connection object.
		/// </summary>
		/// <returns>The number of rows affected.</returns>
		virtual int ExecuteNonQuery() override;

		/// <summary>
		/// Executes the query and returns the first column of the first row in the result
		/// set returned by the query. All other columns and rows are ignored.
		/// </summary>
		/// <returns>The first column of the first row in the result set.</returns>
		virtual Object^ ExecuteScalar() override;

		/// <summary>
		/// Creates a prepared (or compiled) version of the command on the data source.
		/// </summary>
		virtual void Prepare() override;
#pragma endregion
#pragma endregion
	};
}
