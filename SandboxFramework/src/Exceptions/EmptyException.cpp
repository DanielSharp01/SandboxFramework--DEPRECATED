#include "EmptyException.h"

#include <sstream>

namespace Exceptions {
	EmptyException::EmptyException(std::string problem)
		: m_Problem(problem), std::runtime_error("Runtime error") { }

	const char* EmptyException::what() const throw()
	{
		std::stringstream os;
		os.str("");
		os << runtime_error::what() << ": " << m_Problem << " is empty!";

		return os.str().c_str();
	}
}