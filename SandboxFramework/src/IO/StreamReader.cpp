#include "StreamReader.h"

namespace IO
{
	StreamReader::StreamReader(Stream* stream)
		: m_Stream(stream) { }

	StreamReader::~StreamReader()
	{
		Close();
		delete m_Stream;
	}

	char StreamReader::Peek()
	{
		return m_Stream->Peek();
	}

	char StreamReader::Read()
	{
		return m_Stream->Read();
	}

	void StreamReader::Read(char* buffer, unsigned long count)
	{
		m_Stream->Read(buffer, count);
	}

	std::string StreamReader::ReadLine()
	{
		std::string buffer("");
		char c;
		while ((c = Read()) != '\0' && c != '\n')
		{
			buffer += c;
		}

		return buffer;
	}

	std::string StreamReader::ReadToEnd()
	{
		std::string buffer("");
		char c;
		while ((c = Read()) != '\0')
		{
			buffer += c;
		}

		return buffer;
	}

	void StreamReader::Close()
	{
		if (m_Stream->IsOpen()) m_Stream->Close();
	}
}