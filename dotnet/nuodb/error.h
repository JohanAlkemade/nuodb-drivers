#pragma once

namespace NuoDb
{
	/// <summary>
	/// Collects information relevant to a warning or error returned by NuoDb.
	/// </summary>
	[Serializable]
	public ref class NuoDbError sealed
	{
#pragma region Instance Fields
	private:
		int m_lineNumber;
		String^ m_message;
		int m_number;
		String^ m_server;
		String^ m_source;
		Byte^ m_state;
#pragma endregion

#pragma region Construction / Destruction
	internal:
		NuoDbError(String^ server, String^ message, int lineNumber, int number, Byte^ state);
#pragma endregion

#pragma region Properties
	public:
		/// <summary>
		/// Gets the error line number.
		/// </summary>
		property int LineNumber 
		{ 
			int get() { return m_lineNumber; }
		}

		/// <summary>
		/// Gets the error message.
		/// </summary>
		property String^ Message 
		{
			String^ get() { return m_message; }
		}
		
		/// <summary>
		/// Gets the error number.
		/// </summary>
		property int Number 
		{ 
			int get() { return m_number; }
		}

		/// <summary>
		/// Gets the server where the error occurred.
		/// </summary>
		property String^ Server 
		{
			String^ get() { return m_server; }
		}

		/// <summary>
		/// Gets the source of the error.
		/// </summary>
		property String^ Source
		{
			String^ get() { return m_source; }
		}

		/// <summary>
		/// Gets the error state.
		/// </summary>
		property Byte^ State
		{
			Byte^ get() { return m_state; }
		}
#pragma endregion
	};

	[Serializable]
	[ListBindable(false)]
	public ref class NuoDbErrorCollection sealed : System::Collections::ICollection
	{
#pragma region Instance Fields
	private:
		List<NuoDbError^>^ m_errors;
#pragma endregion	

#pragma region Construction / Destruction
	internal:
		NuoDbErrorCollection();
#pragma endregion

#pragma region Properties
	public:
		/// <summary>
		/// Gets the <see cref="NuoDbError"/> at the specified index.
		/// </summary>
		/// <param name="index">The index.</param>
		/// <returns>The <see cref="NuoDbError"/>.</returns>
		/// <exception cref="ArgumentOutOfRangeException">The <paramref name="index"/> does not exist.</exception>
		property NuoDbError^ default[int]
		{
			NuoDbError^ get(int index);
		}
#pragma endregion

#pragma region Methods
	internal:
		void Add(NuoDbError^ e);

	public:
		/// <summary>
		/// Copies the elements of the <see cref="NuoDbErrorCollection"/> collection into an <see cref="Array"/>, starting at the specified index.
		/// </summary>
		/// <param name="a">The <see cref="Array"/> to copy to.</param>
		/// <param name="index">The starting index to copy to.</param>
		/// <exception cref="ArgumentNullException">The <paramref name="a"/> was <see langword="null"/>.</exception>
		/// <exception cref="IndexOutOfRangeException">The <paramref name="index"/> does not exist.</exception>
		void CopyTo(array<NuoDbError^>^ a, int index);
#pragma endregion

#pragma region ICollection Implementation
	public:
		/// <summary>
		/// Gets the number of errors in the collection.
		/// </summary>
		virtual property int Count
		{
			int get() { return m_errors->Count; }
		}

		/// <summary>
		/// Gets a value indicating whether access to the collection is synchronized (thread safe).
		/// </summary>
		virtual property bool IsSynchronized 
		{
			bool get() { return ((System::Collections::IList^)m_errors)->IsSynchronized; }
		}

		/// Gets an object that can be used to synchronize access to the collection.
		virtual property Object^ SyncRoot
		{
			Object^ get() { return this; }
		}

		/// <summary>
		/// Copies the elements of the <see cref="NuoDbErrorCollection"/> collection into an <see cref="Array"/>, starting at the specified index.
		/// </summary>
		/// <param name="a">The <see cref="Array"/> to copy to.</param>
		/// <param name="index">The starting index to copy to.</param>
		/// <exception cref="ArgumentNullException">The <paramref name="a"/> was <see langword="null"/>.</exception>
		/// <exception cref="IndexOutOfRangeException">The <paramref name="index"/> does not exist.</exception>
		virtual void CopyTo(Array^ a, int index);
#pragma endregion

#pragma region IEnumerable Implementation
	public:
		/// <summary>
		/// Returns an enumerator that iterates through the <see cref="NuoDbErrorCollection"/>.
		/// </summary>
		/// <returns>An enumerator that iterates through the <see cref="NuoDbErrorCollection"/>.</returns>
		virtual System::Collections::IEnumerator^ GetEnumerator() { return m_errors->GetEnumerator(); }
#pragma endregion
	};
}
