#pragma once

#include <string>

namespace StringUtils
{
	namespace Convert
	{
		bool ToUnsignedInt(std::string str, unsigned int& out);
		bool ToUnsignedInt(std::string str, int& out);
		bool ToInt(std::string str, int& out);
	}
}