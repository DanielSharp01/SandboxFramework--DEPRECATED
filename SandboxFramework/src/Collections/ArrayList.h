#pragma once

#include "List.h"

namespace Collections {
	template<class T>
	class ArrayList : public List<T>
	{
	private:
		T* m_Arr;
		int m_Count;
		int m_Capacity;
		float m_ReservedCapacity;
	public:
		ArrayList(int capacity = 4, float reservedCapacity = 0.5f)
			: m_Capacity(capacity), m_ReservedCapacity(reservedCapacity)
		{
			m_Arr = new T[capacity];
			m_Count = 0;
		}

		~ArrayList()
		{
			delete[] m_Arr;
		}

		void Clear() override
		{
			m_Arr = new T[m_Capacity];
			m_Count = 0;
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
				m_Arr[i] = m_Arr[i - 1];
			}

			m_Arr[index] = element;
			m_Count++;

			return m_Arr[index];
		}

		T RemoveAt(int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			T removed = m_Arr[index];
			for (int i = index + 1; i < m_Count; i++)
			{
				m_Arr[i - 1] = m_Arr[i];
			}

			m_Count--;

			return removed;
		}

		T Get(int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return m_Arr[index];
		}

		void Set(int index, T value) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			m_Arr[index] = value;
		}

		T& operator[](int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return m_Arr[index];
		}

		const T& operator[](int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return m_Arr[index];
		}

		inline int GetCount() const override { return m_Count; }
	private:
		void reallocate()
		{
			T* newArr = new T[(unsigned int)((float)m_Capacity * (1.0f + m_ReservedCapacity))];
			memcpy(newArr, &m_Arr[0], m_Count * sizeof(T));
			delete m_Arr;
			m_Arr = newArr;
		}
	};
}