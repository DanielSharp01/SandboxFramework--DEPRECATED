#include "Parser.h"

namespace StringUtils
{
	Parser::Parser(std::string source)
	{
		m_Buffer = new StringBuffer(source);
	}

	Parser::~Parser()
	{
		delete m_Buffer;
	}

	void Parser::JumpTo(unsigned int position)
	{
		m_Buffer->JumpTo(position);
	}

	void Parser::JumpToStart()
	{
		m_Buffer->JumpToStart();
	}

	void Parser::JumpToEnd()
	{
		m_Buffer->JumpToEnd();
	}

	void Parser::Step(int ammount)
	{
		m_Buffer->Step(ammount);
	}

	void Parser::StepLength(std::string str)
	{
		m_Buffer->Step(str.length());
	}

	CharType Parser::GetType()
	{
		char c = Get();
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return CharType::Letter;
		else if ((c >= '0' && c <= '9')) return CharType::Digit;
		else if (c == ' ' || c == '\n' || c == 'r' || c == '\t' || c == '\f' || c == 133 || c == 160) return CharType::Whitespace;
		else return CharType::Symbol;
	}

	void Parser::StartTempBuffer()
	{
		m_TmpStart = m_Buffer->GetPosition();
	}

	StringBuffer Parser::RetrieveTempBuffer(bool excludeCurrent)
	{
		return StringBuffer(m_Buffer->GetToFrom(m_TmpStart), excludeCurrent);
	}

	std::string Parser::RetrieveTempString(bool excludeCurrent)
	{
		return m_Buffer->GetToFrom(m_TmpStart, excludeCurrent);
	}

	void Parser::StepUntil(CharType type)
	{
		while (GetType() == type && !m_Buffer->HasEnded()) Step();
	}

	void Parser::StepUntil(char chr)
	{
		while (Get() == chr && !m_Buffer->HasEnded()) Step();
	}

	void Parser::StepUntilNot(CharType type)
	{
		while (GetType() != type && !m_Buffer->HasEnded()) Step();
	}

	void Parser::StepUntilNot(char chr)
	{
		while (Get() != chr && !m_Buffer->HasEnded()) Step();
	}
	
	void Parser::StepUntilNot(std::string str, int stopPoint)
	{
		while (!onString(str, stopPoint) && !m_Buffer->HasEnded())
			Step();
	}

	void Parser::SignError(std::string error)
	{
		int line = 0, column = 0;
		determineLineColumn(line, column);
		m_Exception.AddException(ParserException(error, line, column));
	}

	bool Parser::onString(std::string str, int stopPoint)
	{
		unsigned int pos = m_Buffer->GetPosition();

		if (stopPoint == -1) stopPoint = str.length();
		for (int i = 1; i <= stopPoint; i++)
		{
			m_Buffer->Step(-1);
			if (Get() != str[stopPoint - i]) {
				m_Buffer->JumpTo(pos);
				return false;
			}
		}

		m_Buffer->JumpTo(pos);
		for (int i = stopPoint; i < str.length(); i++)
		{
			if (Get() != str[i]) {
				m_Buffer->JumpTo(pos);
				return false;
			}
			m_Buffer->Step(1);
		}

		m_Buffer->JumpTo(pos);
		return true;
	}


	void Parser::determineLineColumn(int& line, int& column)
	{
		line = 1;
		column = 1;
		const std::string& data = m_Buffer->GetAll();

		for (int i = 0; i < m_Buffer->GetPosition(); i++)
		{
			if (data[i] == '\n')
			{
				line++;
				column = 1;
			}
			else if (data[i] == '\t') column += 4;
			else column++;
		}
	}
}