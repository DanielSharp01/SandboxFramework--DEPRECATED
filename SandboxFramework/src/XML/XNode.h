#pragma once

#include <string>

namespace XML
{
	struct XNode
	{
		virtual std::string ToString(std::string spaces = "") = 0;
	};
}