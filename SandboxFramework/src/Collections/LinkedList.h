#pragma once

#include "List.h"
#include "LinkedElement.h"

namespace Collections {
	template<class T>
	class LinkedList : public List<T>
	{
	private:
		LinkedElement<T>* m_HeadTail;
		int m_Count;
	public:
		LinkedList()
		{
			m_HeadTail = new LinkedElement<T>();
			m_HeadTail->Next = m_HeadTail;
			m_HeadTail->Previous = m_HeadTail;
			m_Count = 0;
		}

		~LinkedList()
		{
			delete m_HeadTail;
		}

		void Clear() override
		{
			LinkedElement<T>* el = m_HeadTail->Next;
			for (int i = 0; i < m_Count; i++)
			{
				LinkedElement<T>* del = el;
				el = el->Next;
				delete del;
			}
			m_HeadTail->Next = m_HeadTail;
			m_HeadTail->Previous = m_HeadTail;

			m_Count = 0;
		}

		T Insert(int index, T element) override
		{
			if (index < 0 || index > m_Count) throw IndexOutOfBoundsException(index);
			LinkedElement<T>* newEl = new LinkedElement<T>(element);
			newEl->linkBefore(getLinkedElement(index));
			m_Count++;
			return *(newEl->Value);
		}

		T RemoveAt(int index) override
		{
			if (index < 0 || index >= m_Count) throw IndexOutOfBoundsException(index);
			LinkedElement<T>* linkedElement = getLinkedElement(index);
			linkedElement->linkOut();
			T removed = *(linkedElement->Value);
			delete linkedElement;
			m_Count--;
			return removed;
		}

		LinkedElement<T>* getLinkedElement(int index) const
		{
			LinkedElement<T>* el = m_HeadTail;
			if (index < m_Count / 2) for (int i = 0; i <= index; i++) el = el->Next;
			else for (int i = 0; i <= m_Count - index; i++) el = el->Previous;
			return el;
		}

		T Get(int index) const override
		{
			if (index < 0 || index >= m_Count) throw IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		void Set(int index, T value) override
		{
			if (index < 0 || index >= m_Count) throw IndexOutOfBoundsException(index);
			getLinkedElement(index)->Value = new T(value);
		}

		T& operator[](int index) override
		{
			if (index < 0 || index >= m_Count) throw IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		const T& operator[](int index) const override
		{
			if (index < 0 || index >= m_Count) throw IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		inline int GetCount() const override { return m_Count; }
	};
}