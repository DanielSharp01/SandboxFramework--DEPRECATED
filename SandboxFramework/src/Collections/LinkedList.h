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

		T Insert(LinkedElement<T>* linkedElement, T element)
		{
			LinkedElement<T>* newEl = new LinkedElement<T>(element);
			newEl->Previous = linkedElement->Previous;
			newEl->Next = linkedElement;
			linkedElement->Previous->Next = newEl;
			linkedElement->Previous = newEl;
			m_Count++;
			return *(newEl->Value);
		}

		T Insert(int index, T element) override
		{
			if (index < 0 || index > m_Count) throw new Exceptions::IndexOutOfBoundsException(index);
			return Insert(GetLinkedElement(index), element);
		}

		T RemoveAt(LinkedElement<T>* linkedElement)
		{
			LinkedElement<T>* lePrev = linkedElement->Previous;
			LinkedElement<T>* leNext = linkedElement->Next;
			lePrev->Next = leNext;
			leNext->Previous = lePrev;
			T removed = *(linkedElement->Value);
			delete linkedElement;
			m_Count--;
			return removed;
		}

		T RemoveAt(int index) override
		{
			if (index < 0 || index >= m_Count) throw new Exceptions::IndexOutOfBoundsException(index);
			return RemoveAt(GetLinkedElement(index));
		}

		LinkedElement<T>* GetLinkedElement(int index)
		{
			LinkedElement<T>* el = headTail;
			for (int i = 0; i <= index; i++)
			{
				el = el->Next;
			}

			return el;
		}

		T Get(int index) override
		{
			if (index < 0 || index >= m_Count) throw new Exceptions::IndexOutOfBoundsException(index);
			return *(GetLinkedElement(index)->Value);
		}

		void Set(LinkedElement<T>* linkedElement, T value)
		{
			*(linkedElement->Value) = value;
		}

		void Set(int index, T value) override
		{
			if (index < 0 || index >= m_Count) throw new Exceptions::IndexOutOfBoundsException(index);
			Set(GetLinkedElement(index), value);
		}

		T& operator[](int index) override
		{
			if (index < 0 || index >= m_Count) throw new Exceptions::IndexOutOfBoundsException(index);
			return *(GetLinkedElement(index)->Value);
		}

		T& operator[](LinkedElement<T>* index)
		{
			return index->Value;
		}

		inline int getCount() override { return m_Count; }
	};
}