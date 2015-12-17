#pragma once

#include "FileReader.h"

namespace IO
{
	class TextReader : public FileReader
	{
	public:
		TextReader(std::string path);

		std::string ReadToEnd();
	};
}