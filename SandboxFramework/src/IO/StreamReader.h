#pragma once

#include "Stream.h"

namespace IO
{
	class StreamReader
	{
	private:
		Stream* m_Stream;
	public:
		StreamReader(Stream* stream);
		~StreamReader();

		char Peek();
		char Read();
		void Read(char* buffer, unsigned long count);
		std::string ReadLine();
		std::string ReadToEnd();

		void Close();
	};
}