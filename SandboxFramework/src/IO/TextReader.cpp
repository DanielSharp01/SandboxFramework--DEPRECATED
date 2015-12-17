#include "TextReader.h"

namespace IO
{
	TextReader::TextReader(std::string path) : FileReader(path, "t") {}

	std::string TextReader::ReadToEnd()
	{
		char* ret = new char[m_Length + 1];
		memset(ret, 0, m_Length + 1);
		fread(ret, 1, m_Length, file);
		return std::string(ret);
	}
}