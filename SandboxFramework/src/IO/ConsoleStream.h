#pragma once

#include "Stream.h"
#include <stdio.h>

namespace IO
{
	//TODO: Add error handling
	class ConsoleStream : public Stream
	{
	public:
		void Write(char* data, unsigned long length) override;
		void Write(std::string data) override;
		char Peek() override;
		char Read() override;

		void Read(char* outData, unsigned long count) override;
		std::string Read(unsigned long length) override;
		void Seek(unsigned long position) override;
		void SeekCurrent(unsigned long position) override;
		void SeekEnd(unsigned long position) override;
		void Flush() override;
		void Close() override;

		unsigned int GetPosition() override;
		unsigned int GetLength() override;

		inline bool IsOpen() override { return true; }
		inline bool IsSeekable() override { return false; }
		inline bool IsWritable() override { return true; }
		inline bool IsReadable() override { return true; }
	};
}