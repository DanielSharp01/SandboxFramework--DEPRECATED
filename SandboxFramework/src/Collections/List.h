#pragma once

#include "IndexOutOfBoundsException.h"
namespace Collections {
	template<class T>
	class List
	{
	public:
		T Add(T element)
		{
			return Insert(GetCount(), element);
		}

		virtual void Clear() = 0;

		virtual T Insert(int index, T element) = 0;
		virtual T RemoveAt(int index) = 0;

		virtual T Get(int index) const = 0;
		virtual void Set(int index, T value) = 0;

		virtual T& operator[] (int index) = 0;
		virtual const T& operator[](int index) const = 0;

		virtual inline int GetCount() const = 0;

		inline T First() const { return Get(0); }
		inline T Last() const { return Get(getCount() - 1); }

		inline bool IsEmpty() const { return GetCount() == 0; };
	};
}