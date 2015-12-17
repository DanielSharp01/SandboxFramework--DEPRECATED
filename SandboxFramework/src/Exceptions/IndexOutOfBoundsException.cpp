#include "IndexOutOfBoundsException.h"

#include <sstream>

namespace Exceptions {
	IndexOutOfBoundsException::IndexOutOfBoundsException()
		: std::runtime_error("Runtime error")
	{ }
	
	IndexOutOfBoundsException::IndexOutOfBoundsException(int problem)
		: m_Problem(problem), std::runtime_error("Runtime error") { }

	const char* IndexOutOfBoundsException::what() const throw()
	{
		std::stringstream os;
		os.str("");
		os << runtime_error::what() << ": index is out of bounds." << " (" << m_Problem << ")";

		return os.str().c_str();
	}
}