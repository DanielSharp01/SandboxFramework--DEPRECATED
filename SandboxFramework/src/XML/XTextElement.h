#pragma once

#include "XNode.h"
#include <string>

namespace XML
{
	struct XTextElement : XNode
	{
		std::string Value;

#ifdef VISUAL_SCHOOL
		XTextElement() {}
#else
		XTextElement() = default;
#endif
		XTextElement(std::string value)
			: Value(value) { }

		std::string ToString(std::string spaces = "") override
		{
			std::string ret = spaces + "";
			for (int i = 0; i < Value.length(); i++)
			{
				ret += Value[i];
				if (Value[i] == '\n') ret += spaces;
			}
			return ret;
		}
	};
}