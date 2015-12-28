#pragma once

#include "Stream.h"
#include <stdio.h>

namespace IO
{
	//TODO: Add error handling
	class ConsoleStream : public Stream
	{
	public:
		void Write(const void* data, int count, int elementSize) override;
		void Write(std::string data) override;
		char Peek() override;
		char Read() override;

		void Read(void* outData, int count, int elementSize) override;
		std::string Read(int length) override;
		void Seek(int position) override;
		void SeekCurrent(int position) override;
		void SeekEnd(int position) override;
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