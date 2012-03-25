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
