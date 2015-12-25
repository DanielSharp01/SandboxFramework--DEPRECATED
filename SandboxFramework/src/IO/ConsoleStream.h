#pragma once
#pragma warning(disable:4996)

#include "Stream.h"
#include <stdio.h>


namespace IO
{
	//TODO: Add error handling
	class ConsoleStream : public Stream
	{
	public:
		ConsoleStream()
		{ }

		void Write(BYTE* data, unsigned long length) override
		{
			fwrite(data, sizeof(BYTE), length, stdout);
		}

		void Write(std::string data) override
		{
			fwrite(data.c_str(), sizeof(BYTE), data.length(), stdout);
		}

		char Peek() override
		{
			int c = fgetc(stdin);
			ungetc(c, stdin);

			if (c == EOF) return '\0';
			return (char)c;
		}

		char Read() override
		{
			int c = fgetc(stdin);
			if (c == EOF) return '\0';
			return (char)c;
		}

		void Read(BYTE* outData, unsigned long count) override
		{
			fread(outData, sizeof(BYTE), count, stdin);
		}

		std::string Read(unsigned long length) override
		{
			char* outData = new char[length + 1];
			fread(outData, sizeof(BYTE), length, stdin);
			outData[length] = '\0';
			return std::string(outData);
		}

		void Seek(unsigned long position) override
		{
			//Error
		}

		void SeekCurrent(unsigned long position) override
		{
			//Error
		}

		void SeekEnd(unsigned long position) override
		{
			//Error
		}

		void Flush() override
		{
			fflush(stdout);
		}

		void Close() override
		{
			//Error
		}

		unsigned int GetPosition() override { /*Error*/ return -1; }
		unsigned int GetLength() override { /*Error*/ return -1; }

		bool IsOpen() override { return true; }
		bool IsSeekable() override { return false; }
		bool IsWritable() override { return true; }
		bool IsReadable() override { return true; }
	};
}