#pragma once

#include "Stream.h"

namespace IO
{
	class StreamWriter
	{
	private:
		Stream* m_Stream;
	public:
		StreamWriter(Stream* stream)
			: m_Stream(stream) { }
		
		~StreamWriter()
		{
			Close();
			delete m_Stream;
		}

		void Write(char character)
		{
			m_Stream->Write(&character, 1);
		}

		void Write(char* buffer, unsigned long count)
		{
			m_Stream->Write(buffer, count);
		}

		void Write(std::string str)
		{
			m_Stream->Write(str);
		}

		void WriteLine(std::string line)
		{
			m_Stream->Write(line + "\n");
		}

		void Flush()
		{
			m_Stream->Flush();
		}

		void Close()
		{
			if (m_Stream->IsOpen()) m_Stream->Close();
		}
	};
}