#pragma once

#include "Stream.h"

namespace IO
{
	class StreamWriter
	{
	private:
		Stream* m_Stream;
	public:
		StreamWriter(Stream* stream);
		~StreamWriter();

		void Write(char character);
		void Write(const void* buffer, int count, int elementSize);
		void Write(std::string str);
		void WriteLine(std::string line);

		void Flush();
		void Close();
	};
}