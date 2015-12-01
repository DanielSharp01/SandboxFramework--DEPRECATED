#pragma once

#include "../Exceptions/EmptyException.h"
#include "LinkedList.h"

namespace Collections
{
	template<class T>
	class Queue
	{
	private:
		LinkedList<T> data;
	public:
		T Peek()
		{
			if (isEmpty()) throw new Exceptions::EmptyException("Queue");
			return data[0];
		}

		T Deque()
		{
			if (isEmpty()) throw new Exceptions::EmptyException("Queue");
			return data.RemoveAt(0);
		}

		void Enque(T value) { data.Add(value); }

		inline int getCount() { return data.getCount(); }
		inline bool isEmpty() { return getCount() == 0; };
	};
}