#pragma once

#include <string>

namespace Exceptions
{
	class KeyNotFoundException
	{
	private:
		std::string m_Key;
	public:
		KeyNotFoundException(std::string key)
			: m_Key(key)
		{ }

		std::string what() const {
			return m_Key + " was not found!";
		}
	};
}