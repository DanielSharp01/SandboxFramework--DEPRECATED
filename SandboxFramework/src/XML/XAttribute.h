#pragma once

#include <string>

namespace XML
{
	struct XAttribute
	{
		std::string Name;
		std::string Value;

#ifdef VISUAL_SCHOOL
		XAttribute() {}
#else
		XAttribute() = default;
#endif

		XAttribute(std::string name, std::string value)
			: Name(name), Value(value)
		{ }

		std::string ToString()
		{
			return Name + " = \"" + Value + "\"";
		}
	};
}