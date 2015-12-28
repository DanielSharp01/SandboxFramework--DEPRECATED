#pragma once

#include <string>

namespace IO
{
	class Stream
	{
	public:
		virtual void Write(char* data, unsigned long length) = 0;
		virtual void Write(std::string data) = 0;

		virtual char Peek() = 0;
		virtual char Read() = 0;
		virtual void Read(char* outData, unsigned long count) = 0;
		virtual std::string Read(unsigned long length) = 0;
		virtual void Seek(unsigned long position) = 0;
		virtual void SeekCurrent(unsigned long position) = 0;
		virtual void SeekEnd(unsigned long position) = 0;

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