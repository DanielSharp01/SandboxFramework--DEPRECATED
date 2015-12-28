#pragma once

#include "Stream.h"
#include <stdio.h>


namespace IO
{
	enum FileAccess
	{
		ReadText,
		WriteText,
		ReadWriteText,
		ReadBinary,
		WriteBinary,
		ReadWriteBinary
	};

	enum FileOpenMode
	{
		Create,
		Append,
		Open
	};
	
	//TODO: Add error handling
	class FileStream : public Stream
	{
	private:
		FILE* m_File;
		unsigned int m_Position;
		unsigned int m_Length;
		FileAccess m_Access;
		bool m_Writable;
		bool m_Readable;
	public:
		FileStream(std::string path, FileAccess access = FileAccess::ReadText, FileOpenMode openMode = FileOpenMode::Open);
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

		inline unsigned int GetPosition() override { return m_Position; }
		inline unsigned int GetLength() override { return m_Length; }

		inline bool IsOpen() override { return (m_File != NULL); }
		inline bool IsSeekable() override { return true; }
		inline bool IsWritable() override { return m_Writable; }
		inline bool IsReadable() override { return m_Readable; }
	private:
		std::string getMode(FileAccess access, FileOpenMode openMode);
	};
}