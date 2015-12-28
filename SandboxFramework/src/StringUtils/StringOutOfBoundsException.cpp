#include "StringOutOfBoundsException.h"

namespace StringUtils {
	StringOutOfBoundsException::StringOutOfBoundsException(std::string str, int index)
		: m_String(str), m_Index(index)
	{ }

	
	std::string StringOutOfBoundsException::Message() const
	{
		return "Runtime Exception: Index out of bounds for string \"" + m_String + "\" indexed with " + std::to_string(m_Index);
	}
}