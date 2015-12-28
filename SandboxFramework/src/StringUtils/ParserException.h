#pragma once
#include "../Debug/Exception.h"

namespace StringUtils {
	class ParserException : public Debug::Exception
	{
	private:
		std::string m_Message;
		int m_Line;
		int m_Column;
	public:
		ParserException() = default;
		ParserException(std::string message, int line, int columnn);
		std::string Message() const override;
	};
}