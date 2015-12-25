#pragma once

#pragma once

#include "Stream.h"

namespace IO
{
	class StreamReader
	{
	private:
		Stream* m_Stream;
	public:
		StreamReader(Stream* stream)
			: m_Stream(stream) { }

		~StreamReader()
		{
			Close();
			delete m_Stream;
		}

		char Peek()
		{
			return m_Stream->Peek();
		}

		char Read()
		{
			return m_Stream->Read();
		}

		void Read(char* buffer, unsigned long count)
		{
			m_Stream->Read(buffer, count);
		}

		std::string ReadLine()
		{
			std::string buffer("");
			char c;
			while ((c = Read()) != '\0' && c != '\n')
			{
				buffer += c;
			}

			return buffer;
		}

		std::string ReadToEnd()
		{
			std::string buffer("");
			char c;
			while ((c = Read()) != '\0')
			{
				buffer += c;
			}

			return buffer;
		}

		void Close()
		{
			if (m_Stream->IsOpen()) m_Stream->Close();
		}
	};
}