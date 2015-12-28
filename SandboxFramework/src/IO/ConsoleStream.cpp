#include "ConsoleStream.h"
#include "IOException.h"

namespace IO
{
	void ConsoleStream::Write(char* data, unsigned long length)
	{
		fwrite(data, sizeof(char), length, stdout);
	}

	void ConsoleStream::Write(std::string data)
	{
		fwrite(data.c_str(), sizeof(char), data.length(), stdout);
	}

	char ConsoleStream::Peek()
	{
		int c = fgetc(stdin);
		ungetc(c, stdin);

		if (c == EOF) return '\0';
		return (char)c;
	}

	char ConsoleStream::Read()
	{
		int c = fgetc(stdin);
		if (c == EOF) return '\0';
		return (char)c;
	}

	void ConsoleStream::Read(char* outData, unsigned long count)
	{
		fread(outData, sizeof(char), count, stdin);
	}

	std::string ConsoleStream::Read(unsigned long length)
	{
		char* outData = new char[length + 1];
		fread(outData, sizeof(char), length, stdin);
		outData[length] = '\0';
		return std::string(outData);
	}

	void ConsoleStream::Seek(unsigned long position)
	{
		throw IOException("Trying to seek console stream.");
	}

	void ConsoleStream::SeekCurrent(unsigned long position)
	{
		throw IOException("Trying to seek console stream.");
	}

	void ConsoleStream::SeekEnd(unsigned long position)
	{
		throw IOException("Trying to seek console stream.");
	}

	void ConsoleStream::Flush()
	{
		fflush(stdout);
	}

	void ConsoleStream::Close()
	{
		throw IOException("Trying to close the console stream.");
	}

	unsigned int ConsoleStream::GetPosition()
	{
		throw IOException("Trying to get position of console stream.");
	}

	unsigned int ConsoleStream::GetLength()
	{
		throw IOException("Trying to get length of console stream.");
	}
}