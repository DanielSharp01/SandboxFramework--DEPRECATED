#pragma once

#include <stdexcept>
#include <string>

namespace IO {
	class IOException : public std::runtime_error
	{
	private:
		std::string m_String;
	public:
		IOException(std::string str);
		virtual const char* what() const throw();
	};
}