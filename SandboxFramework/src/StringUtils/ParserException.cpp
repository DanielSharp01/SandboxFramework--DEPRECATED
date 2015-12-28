#include "ParserException.h"

namespace StringUtils
{
	ParserException::ParserException(std::string message, int line, int column)
		: m_Message(message), m_Line(line), m_Column(column)
	{ }

	std::string ParserException::Message() const
	{
		return "Parsing Exception: " + m_Message + " in line " + std::to_string(m_Line) + " at column " + std::to_string(m_Column);
	}
}