#pragma once

#include "../Exceptions/EmptyException.h"
#include "LinkedList.h"

namespace Collections
{
	template<class T>
	class Queue
	{
	private:
		LinkedList<T>* m_Data;
	public:
		Queue()
		{
			m_Data = new LinkedList<T>();
		}

		~Queue()
		{
			delete m_Data;
		}

		void Clear()
		{
			m_Data->Clear();
		}

		T Peek()
		{
			if (IsEmpty()) throw IndexOutOfBoundsException(0);
			return (*m_Data)[0];
		}

		T Deque()
		{
			if (IsEmpty()) throw IndexOutOfBoundsException(0);
			return m_Data->RemoveAt(0);
		}

		void Enque(T value) { m_Data->Add(value); }

		inline int GetCount() const { return m_Data->GetCount(); }
		inline bool IsEmpty() const { return GetCount() == 0; };
	};
}