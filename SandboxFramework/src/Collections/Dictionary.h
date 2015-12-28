#pragma once

#include "ArrayList.h"

namespace Collections {
	template<class K, class V>
	class Dictionary
	{
	private:
		ArrayList<K>* m_Keys;
		ArrayList<V>* m_Values;
	public:
		Dictionary()
		{
			m_Keys = new ArrayList<K>();
			m_Values = new ArrayList<V>();
		}

		~Dictionary()
		{
			delete m_Keys;
			delete m_Values;
		}

		void Clear()
		{
			m_Keys->Clear();
			m_Values->Clear();
		}

		V Add(K key, V value)
		{
			m_Keys->Add(key);
			return m_Values->Add(value);
		}

		V RemoveAt(K key)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw IndexOutOfBoundsException(index);
			m_Keys->RemoveAt(index);
			return m_Values->RemoveAt(index);
		}

		V Get(K key) const
		{
			int index = findKeyIndex(key);
			if (index == -1) throw IndexOutOfBoundsException(index);
			return (*m_Values)[index];
		}

		void Set(K key, V value)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw IndexOutOfBoundsException(index);
			return (*m_Values)[index] = value;
		}

		V& operator[] (K key)
		{
			int index = findKeyIndex(key);
			if (index == -1) throw IndexOutOfBoundsException(index);
			return (*m_Values)[index];
		}

		const V& operator[] (K key) const
		{
			int index = findKeyIndex(key);
			if (index == -1) throw IndexOutOfBoundsException(index);
			return (*m_Values)[index];
		}

		bool ContainsKey(K key) const
		{
			return findKeyIndex(key) != -1;
		}

		inline ArrayList<K>* GetKeys() const { return m_Keys; }
		inline ArrayList<V>* GetValues() const { return m_Values; }

		inline int GetCount() const { return m_Keys->GetCount(); }
		inline bool IsEmpty() const { return GetCount() == 0; };
	private:
		int findKeyIndex(K key) const
		{
			for (int i = 0; i < GetCount(); i++)
			{
				if ((*m_Keys)[i] == key) return i;
			}

			return -1;
		}
	};
}