#pragma once
#include "../Debug/Exception.h"

namespace StringUtils {
	class StringOutOfBoundsException : public Debug::Exception
	{
	private:
		std::string m_String;
		int m_Index;
	public:
		StringOutOfBoundsException(std::string str, int index);
		std::string Message() const override;
	};
}