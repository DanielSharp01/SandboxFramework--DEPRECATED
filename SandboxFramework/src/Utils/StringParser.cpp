#include "StringParser.h"

namespace StringUtils
{
	StringParser::StringParser(const std::string& stream)
		: m_Stream(stream), m_Position(0)
	{ }

	void StringParser::Goto(unsigned int position)
	{
		m_Position = position;
	}

	void StringParser::Step(int steps)
	{
		m_Position += steps;
	}

	void StringParser::SkipUntilNextLine()
	{
		while (m_Stream[m_Position] != '\n') m_Position++;
		m_Position++;
	}

	void StringParser::SkipString(std::string str)
	{
		m_Position += str.length();
	}

	void StringParser::SkipUntilNextNonSpace()
	{
		while (m_Stream[m_Position] == ' ') m_Position++;
	}

	std::string StringParser::GetStringUntilNextWhiteSpace()
	{
		int start = m_Position;
		int length = 0;
		while (m_Stream[m_Position] != ' ' && m_Stream[m_Position] != '\n')
		{
			m_Position++;
			length++;
		}

		return m_Stream.substr(start, length);
	}

	std::string StringParser::GetStringUntilNextCharacter(char chr)
	{
		int start = m_Position;
		int length = 0;
		while (m_Stream[m_Position] != chr)
		{
			m_Position++;
			length++;
		}

		return m_Stream.substr(start, length);
	}

	int StringParser::GetIntFromString(std::string str) const
	{
		return atoi(str.c_str());
	}
}