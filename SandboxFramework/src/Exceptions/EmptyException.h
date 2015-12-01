#pragma once

#include <string>

namespace Exceptions
{
	class EmptyException
	{
	private:
		std::string m_What;
	public:
		EmptyException(std::string whatIsEmpty)
			: m_What(whatIsEmpty)
		{ }
		std::string what() const {
			return m_What + " is empty!";
		}
	};
}