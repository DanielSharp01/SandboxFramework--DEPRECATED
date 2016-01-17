#include "FileStream.h"

#include "IOException.h"

namespace IO
{
	FileStream::FileStream(std::string path, FileAccess access, FileOpenMode openMode)
	{
		std::string mode = getMode(access, openMode);

		if (mode == "e") throw IOException("Invalid FileAccess FileOpenMode combination. Hint: Use Read with Open and Write with Create.");
		m_Writable = mode[0] == 'w' || (mode.length() > 1 && mode[1] == '+');
		m_Readable = mode[0] == 'r';
		m_File = fopen(path.c_str(), mode.c_str());
		if (m_File == NULL) throw IOException("Cannot open file: " + path);

		fseek(m_File, 0, SEEK_END);
		m_Length = ftell(m_File);
		fseek(m_File, 0, SEEK_SET);
	}

	void FileStream::Write(const void* data, int count, int elementSize)
	{
		fwrite(data, elementSize, count, m_File);
		m_Length += count;
		m_Position += count;
	}

	void FileStream::Write(std::string data)
	{
		fwrite(data.c_str(), sizeof(char), data.length(), m_File);
		m_Length += data.length();
		m_Position += data.length();
	}

	char FileStream::Peek()
	{
		int c = fgetc(m_File);
		ungetc(c, m_File);

		if (m_Position >= m_Length) return '\0';
		return (char)c;
	}

	char FileStream::Read()
	{
		int c = fgetc(m_File);
		m_Position++;

		if (m_Position >= m_Length) return '\0';
		return (char)c;
	}

	void FileStream::Read(void* outData, int count, int elementSize)
	{
		fread(outData, elementSize, count, m_File);
		m_Position += count;
	}

	std::string FileStream::Read(int length)
	{
		char* outData = new char[length + 1];
		fread(outData, sizeof(char), length, m_File);
		outData[length] = '\0';
		m_Position += length;
		return std::string(outData);
	}

	void FileStream::Seek(int position)
	{
		fseek(m_File, position, SEEK_SET);
	}

	void FileStream::SeekCurrent(int position)
	{
		fseek(m_File, position, SEEK_CUR);
	}

	void FileStream::SeekEnd(int position)
	{
		fseek(m_File, position, SEEK_END);
	}

	void FileStream::Flush()
	{
		fflush(m_File);
	}

	void FileStream::Close()
	{
		fclose(m_File);
		m_File = NULL;
	}

	std::string FileStream::getMode(FileAccess access, FileOpenMode openMode)
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
}