#pragma once

#include "../Exceptions/EmptyException.h"
#include "LinkedList.h"

namespace Collections
{
	template<class T>
	class Stack
	{
	private:
		LinkedList<T> data;
	public:
		T Peek()
		{
			if (isEmpty()) throw new Exceptions::EmptyException("Stack");
			return data[0];
		}

		T Pop() 
		{
			if (isEmpty()) throw new Exceptions::EmptyException("Stack");
			return data.RemoveAt(0);
		}

		void Push(T value) { data.Insert(0, value); }

		inline int getCount() { return data.getCount(); }
		inline bool isEmpty() { return getCount() == 0; };
	};
}