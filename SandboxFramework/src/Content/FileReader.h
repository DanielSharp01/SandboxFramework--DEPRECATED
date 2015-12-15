#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>

namespace SandboxFramework
{
	namespace Content
	{
		//TODO: Add functionality
		class FileReader
		{
		private:
			FILE* file;
			int m_Position;
			int m_Length;
		public:
			FileReader(std::string path, std::string mode);
			~FileReader();

			inline int GetPosition() const { return m_Position; }
			inline int GetLength() const { return m_Length; }

			void Seek(int position);
			std::string ReadToEnd();
		};
	}
}