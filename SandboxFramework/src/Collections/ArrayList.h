#pragma once

#include "List.h"

namespace Collections {
	template<class T>
	class ArrayList : public List<T>
	{
	private:
		T* arr;
		int m_Count;
		int m_Capacity;
		float m_ReservedCapacity;
	public:
		ArrayList(int capacity = 4, float reservedCapacity = 0.5f)
			: m_Capacity(capacity), m_ReservedCapacity(reservedCapacity)
		{
			arr = new T[capacity];
			m_Count = 0;
		}

		~ArrayList()
		{
			delete[] arr;
		}

		void Clear() override
		{
			arr = new T[m_Capacity];
		}

		T Insert(int index, T element) override
		{
			if (index < 0 || index > m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			if (m_Capacity < m_Count + 1)
			{
				reallocate();
			}
			for (int i = m_Count; i > index; i--)
			{
				arr[i] = arr[i - 1];
			}

			arr[index] = element;
			m_Count++;

			return arr[index];
		}

		T RemoveAt(int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			T removed = arr[index];
			for (int i = index + 1; i < m_Count; i++)
			{
				arr[i - 1] = arr[i];
			}

			m_Count--;

			return removed;
		}

		T Get(int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return arr[index];
		}

		void Set(int index, T value) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			arr[index] = value;
		}

		T& operator[](int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return arr[index];
		}

		const T& operator[](int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return arr[index];
		}

		inline int GetCount() const override { return m_Count; }
	private:
		void reallocate()
		{
			T* newArr = new T[(unsigned int)((float)m_Capacity * (1.0f + m_ReservedCapacity))];
			memcpy(newArr, &arr[0], m_Count * sizeof(T));
			delete arr;
			arr = newArr;
		}
	};
}