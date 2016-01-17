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
#ifdef VISUAL_SCHOOL
		ParserException() {}
#else
		ParserException() = default;
#endif
		ParserException(std::string message, int line, int columnn);
		std::string Message() const override;
	};
}