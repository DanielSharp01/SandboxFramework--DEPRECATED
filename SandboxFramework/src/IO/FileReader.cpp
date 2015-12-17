#include "FileReader.h"

namespace IO
{
	FileReader::FileReader(std::string path, std::string mode)
	{
		mode = "r" + mode;
		file = fopen(path.c_str(), mode.c_str());

		fseek(file, 0, SEEK_END);
		m_Length = ftell(file);
		fseek(file, 0, SEEK_SET);
	}

	FileReader::~FileReader()
	{
		fclose(file);
		file = NULL;
	}

	void FileReader::Seek(int position)
	{
		fseek(file, 0, SEEK_SET);
		m_Position = position;
	}
}