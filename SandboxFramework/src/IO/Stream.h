#pragma once

#include <string>

namespace IO
{
	class Stream
	{
	public:
		virtual void Write(const void* data, int count, int elementSize) = 0;
		virtual void Write(std::string data) = 0;

		virtual char Peek() = 0;
		virtual char Read() = 0;
		virtual void Read(void* outData, int count, int elementSize) = 0;
		virtual std::string Read(int length) = 0;
		virtual void Seek(int position) = 0;
		virtual void SeekCurrent(int position) = 0;
		virtual void SeekEnd(int position) = 0;

		virtual void Flush() = 0;
		virtual void Close() = 0;

		virtual unsigned int GetPosition() = 0;
		virtual unsigned int GetLength() = 0;

		virtual bool IsOpen() = 0;
		virtual bool IsSeekable() = 0;

		virtual bool IsWritable() = 0;
		virtual bool IsReadable() = 0;
	};
}