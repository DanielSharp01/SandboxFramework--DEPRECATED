#pragma once

#include <stdexcept>
#include <sstream>

namespace Exceptions {
	class IndexOutOfBoundsException : public std::runtime_error
	{
	private:
		int m_Problem;
	public:
		IndexOutOfBoundsException();
		IndexOutOfBoundsException(int problem);
		virtual const char* what() const throw();
	};
}