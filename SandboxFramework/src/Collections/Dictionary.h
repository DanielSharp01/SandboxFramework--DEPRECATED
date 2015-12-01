#pragma once

#include "../Exceptions/KeyNotFoundException.h"
#include "ArrayList.h"

namespace Collections {
	template<class T, class V>
	class Dictionary
	{
	private:
		ArrayList<T>* m_Keys;
		ArrayList<V>* m_Values;
	public:
		Dictionary()
		{
			m_Keys = new ArrayList<T>();
			m_Values = new ArrayList<V>();
		}

		~Dictionary()
		{
			delete m_Keys;
			delete m_Values;
		}

		V Add(T key, V value)
		{
			m_Keys->Add(key);
			return m_Values->Add(value);
		}

		V RemoveAt(T key)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw new Exceptions::KeyNotFoundException("std::to_string(key)");
			m_Keys->RemoveAt(index);
			return m_Values->RemoveAt(index);
		}

		V Get(T key)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw new Exceptions::KeyNotFoundException("std::to_string(key)");
			return (*m_Values)[index];
		}

		void Set(T key, V value)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw new Exceptions::KeyNotFoundException("std::to_string(key)");
			return (*m_Values)[index] = value;
		}

		V& operator[] (T key)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw new Exceptions::KeyNotFoundException("std::to_string(key)"); //TODO::Think about this or just make non parameter exceptions
			return (*m_Values)[index];
		}

		bool ContainsKey(T key)
		{
			return findKeyIndex(key) != -1;
		}

		inline ArrayList<T>* getKeys() { return m_Keys; } //TODO: CONST and IMPLEMENT non-reference array operator (the friend)
		inline ArrayList<V>* getValues() { return m_Values; }

		inline int getCount() { return m_Keys->getCount(); }
		inline bool isEmpty() { return getCount() == 0; };
	private:
		int findKeyIndex(T key)
		{
			for (int i = 0; i < getCount(); i++)
			{
				if ((*m_Keys)[i] == key) return i;
			}

			return -1;
		}
	};
}