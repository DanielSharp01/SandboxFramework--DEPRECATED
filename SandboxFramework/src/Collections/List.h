#pragma once

#include "../Exceptions/IndexOutOfBoundsException.h"

namespace Collections {
	template<class T>
	class List
	{
	public:
		T Add(T element)
		{
			return Insert(getCount(), element);
		}

		virtual T Insert(int index, T element) = 0;
		virtual T RemoveAt(int index) = 0;

		virtual T Get(int index) = 0;
		virtual void Set(int index, T value) = 0;

		virtual T& operator[] (int index) = 0;

		virtual inline int getCount() = 0;
		inline bool isEmpty() { return getCount() == 0; };
	};
}