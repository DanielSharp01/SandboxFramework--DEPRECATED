#pragma once

#include "../Exceptions/EmptyException.h"
#include "LinkedList.h"

namespace Collections
{
	template<class T>
	class Stack
	{
	private:
		LinkedList<T>& m_Data;
	public:
		Stack()
		{
			m_Data = LinkedList<T>();
		}

		~Stack()
		{
			delete m_Data;
		}

		T Peek()
		{
			if (IsEmpty()) throw Exceptions::EmptyException("Cannot peek as the Stack ");
			return m_Data[0];
		}

		T Pop() 
		{
			if (IsEmpty()) throw Exceptions::EmptyException("Cannot pop as the Stack ");
			return m_Data.RemoveAt(0);
		}

		void Push(T value) { m_Data.Insert(0, value); }

		inline int GetCount() const { return m_Data.GetCount(); }
		inline bool IsEmpty() const { return GetCount() == 0; };
	};
}