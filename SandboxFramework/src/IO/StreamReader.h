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
		void Read(void* buffer, int count, int elementSize);
		std::string ReadLine();
		std::string ReadToEnd();

		void Close();
	};
}