#pragma once

#include <string>
namespace Debug
{
	class Exception
	{
		virtual std::string Message() const = 0;
	};
}