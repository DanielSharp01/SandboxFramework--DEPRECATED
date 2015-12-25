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
		FileStream(std::string path, FileAccess access = FileAccess::ReadText, FileOpenMode openMode = FileOpenMode::Open)
		{
			std::string mode = getMode(access, openMode);
			//TODO: Throw legit expection
			if (mode == "e") throw -1;
			m_Writable = mode[0] == 'w' || (mode.length() > 1 && mode[1] == '+');
			m_Readable = mode[0] == 'r';
			m_File = fopen(path.c_str(), mode.c_str());
			fseek(m_File, 0, SEEK_END);
			m_Length = ftell(m_File);
			fseek(m_File, 0, SEEK_SET);
		}

		void Write(BYTE* data, unsigned long length) override
		{
			fwrite(data, sizeof(BYTE), length, m_File);
			m_Length += length;
			m_Position += length;
		}

		void Write(std::string data) override
		{
			fwrite(data.c_str(), sizeof(BYTE), data.length(), m_File);
			m_Length += data.length();
			m_Position += data.length();
		}

		char Peek() override
		{
			int c = fgetc(m_File);
			ungetc(c, m_File);

			if (c == EOF) return '\0';
			return (char)c;
		}

		char Read() override
		{
			int c = fgetc(m_File);
			m_Position++;

			if (c == EOF) return '\0';
			return (char)c;
		}

		void Read(BYTE* outData, unsigned long count) override
		{
			fread(outData, sizeof(BYTE), count, m_File);
			m_Position += count;
		}

		std::string Read(unsigned long length) override
		{
			char* outData = new char[length + 1];
			fread(outData, sizeof(BYTE), length, m_File);
			outData[length] = '\0';
			m_Position += length;
			return std::string(outData);
		}

		void Seek(unsigned long position) override
		{
			fseek(m_File, position, SEEK_SET);
		}

		void SeekCurrent(unsigned long position) override
		{
			fseek(m_File, position, SEEK_CUR);
		}

		void SeekEnd(unsigned long position) override
		{
			fseek(m_File, position, SEEK_END);
		}

		void Flush() override
		{
			fflush(m_File);
		}

		void Close() override
		{
			fclose(m_File);
			m_File = NULL;
		}

		inline unsigned int GetPosition() override { return m_Position; }
		inline unsigned int GetLength() override { return m_Length; }

		bool IsOpen() override { return (m_File != NULL); }
		bool IsSeekable() override { return true; }
		bool IsWritable() override { return m_Writable; }
		bool IsReadable() override { return m_Readable; }
	private:
		std::string getMode(FileAccess access, FileOpenMode openMode)
		{
			if (openMode == FileOpenMode::Open)
			{
				if (access == FileAccess::ReadText) return "r";
				else if (access == FileAccess::ReadBinary) return "rb";
				else if (access == FileAccess::ReadWriteText) return "r+";
				else if (access == FileAccess::ReadWriteBinary) return "rb+";
				else return "e";
			}
			else if (openMode == FileOpenMode::Create)
			{
				if (access == FileAccess::WriteText) return "w";
				else if (access == FileAccess::WriteBinary) return "wb";
				else if (access == FileAccess::ReadWriteText) return "r+";
				else if (access == FileAccess::ReadWriteBinary) return "rb+";
				else return "e";
			}
			else /*if (openMode == FileOpenMode::Append)*/
			{
				if (access == FileAccess::WriteText) return "a";
				else if (access == FileAccess::WriteBinary) return "ab";
				else if (access == FileAccess::ReadWriteText) return "a+";
				else if (access == FileAccess::ReadWriteBinary) return "ab+";
				else return "e";
			}
		}
	};
}