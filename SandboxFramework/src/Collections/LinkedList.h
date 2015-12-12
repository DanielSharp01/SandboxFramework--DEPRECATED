#pragma once

#include "List.h"
#include "LinkedElement.h"

namespace Collections {
	template<class T>
	class LinkedList : public List<T>
	{
	private:
		LinkedElement<T>* headTail;
		int m_Count;
	public:
		LinkedList()
		{
			headTail = new LinkedElement<T>();
			headTail->Next = headTail;
			headTail->Previous = headTail;
			m_Count = 0;
		}

		~LinkedList()
		{
			delete headTail;
		}

		T Insert(int index, T element) override
		{
			if (index < 0 || index > m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			LinkedElement<T>* newEl = new LinkedElement<T>(element);
			newEl->linkBefore(getLinkedElement(index));
			m_Count++;
			return *(newEl->Value);
		}

		T RemoveAt(int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			getLinkedElement(index)->linkOut();
			T removed = *(linkedElement->Value);
			delete linkedElement;
			m_Count--;
			return removed;
		}

		LinkedElement<T>* getLinkedElement(int index)
		{
			LinkedElement<T>* el = headTail;
			if (index < m_Count / 2) for (int i = 0; i <= index; i++) el = el->next;
			else for (int i = 0; i <= m_Count - index; i++) el = el->previous;
			return el;
		}

		T Get(int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		void Set(int index, T value) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			getLinkedElement(index)->Value = value;
		}

		T& operator[](int index) override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		const T& operator[](int index) const override
		{
			if (index < 0 || index >= m_Count) throw Exceptions::IndexOutOfBoundsException(index);
			return *(getLinkedElement(index)->Value);
		}

		inline int GetCount() const override { return m_Count; }
	};
}