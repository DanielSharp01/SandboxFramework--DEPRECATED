#include "StreamWriter.h"

namespace IO
{
	StreamWriter::StreamWriter(Stream* stream)
		: m_Stream(stream) { }

	StreamWriter::~StreamWriter()
	{
		Close();
		delete m_Stream;
	}

	void StreamWriter::Write(char character)
	{
		m_Stream->Write(&character, 1);
	}

	void StreamWriter::Write(char* buffer, unsigned long count)
	{
		m_Stream->Write(buffer, count);
	}

	void StreamWriter::Write(std::string str)
	{
		m_Stream->Write(str);
	}

	void StreamWriter::WriteLine(std::string line)
	{
		m_Stream->Write(line + "\n");
	}

	void StreamWriter::Flush()
	{
		m_Stream->Flush();
	}

	void StreamWriter::Close()
	{
		if (m_Stream->IsOpen()) m_Stream->Close();
	}
}