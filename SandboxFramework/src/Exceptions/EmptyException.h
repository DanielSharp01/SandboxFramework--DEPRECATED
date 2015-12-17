#pragma once

#include <stdexcept>
#include <string>

namespace Exceptions {
	class EmptyException : public std::runtime_error
	{
	private:
		std::string m_Problem;
	public:
		EmptyException(std::string problem);
		virtual const char* what() const throw();
	};
}