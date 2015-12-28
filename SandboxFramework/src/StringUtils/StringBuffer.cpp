#include "StringBuffer.h"
#include "StringOutOfBoundsException.h"

namespace StringUtils
{
	StringBuffer::StringBuffer()
		: m_Data(""), m_Position(0)
	{ }

	StringBuffer::StringBuffer(std::string data, unsigned int start)
		: m_Data(data), m_Position(start) { }

	void StringBuffer::Clear()
	{
		m_Data = "";
		m_Position = 0;
		m_PositionStack.Clear();
	}

	void StringBuffer::JumpTo(unsigned int position)
	{
		if (position > m_Data.length()) throw StringOutOfBoundsException(m_Data, position);
		m_Position = position;
	}

	void StringBuffer::JumpToStart()
	{
		m_Position = 0;
	}

	void StringBuffer::JumpToEnd()
	{
		m_Position = GetLength() - 1;
	}

	void StringBuffer::Step(int ammount)
	{
		if (m_Position + ammount > m_Data.length()) throw StringOutOfBoundsException(m_Data, m_Position + ammount);
		m_Position += ammount;
	}

	void StringBuffer::PushPosition()
	{
		m_PositionStack.Push(m_Position);
	}

	void StringBuffer::PopPosition()
	{
		m_Position = m_PositionStack.Pop();
	}

	char StringBuffer::Get()
	{
		if (m_Position > m_Data.length()) throw StringOutOfBoundsException(m_Data, m_Position);
		if (m_Position == m_Data.length()) return '\0';
		return m_Data[m_Position];
	}

	std::string StringBuffer::GetFrom(int length)
	{
		if (length == -1) return m_Data.substr(m_Position);
		else return m_Data.substr(m_Position, length);
	}

	std::string StringBuffer::GetTo(int length)
	{
		if (length == -1) return m_Data.substr(0, m_Position + 1);
		else return m_Data.substr(m_Position - length, length);
	}

	std::string StringBuffer::GetToFrom(unsigned int start, bool excludeCurrent)
	{
		return m_Data.substr(start, m_Position - start + (excludeCurrent ? 0 : 1));
	}

	void StringBuffer::Add(std::string data)
	{
		m_Data.insert(m_Position + 1, data);
	}

	std::string StringBuffer::Pop()
	{
		std::string store = GetFrom();
		m_Data.erase(m_Position);
		return store;
	}

	std::string StringBuffer::PopTo()
	{
		std::string store = GetFrom();
		m_Data.erase(0, m_Position + 1);
		return store;
	}
}