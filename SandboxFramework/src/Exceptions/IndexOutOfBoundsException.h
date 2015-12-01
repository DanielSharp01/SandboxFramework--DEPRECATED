#pragma once

#include <string>

namespace Exceptions
{
	class IndexOutOfBoundsException
	{
	private:
		int m_Out;
	public:
		IndexOutOfBoundsException(int out)
			: m_Out(out)
		{ }

		std::string what() const {
			return std::to_string(m_Out) + " is out of bounds!";
		}
	};
}