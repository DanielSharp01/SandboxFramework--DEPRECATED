#include "IOException.h"

namespace IO {
	IOException::IOException(std::string str)
		: std::runtime_error("Runtime error: IO Exception:"), m_String(str)
	{ }

	const char* IOException::what() const throw()
	{
		std::string ret = std::string(runtime_error::what());
		ret += " " + m_String;
		return ret.c_str();
	}
}