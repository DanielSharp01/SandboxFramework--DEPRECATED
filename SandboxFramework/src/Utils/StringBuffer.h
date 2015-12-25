#pragma once

#include "../Collections/Stack.h"
#include <string>

namespace StringUtils
{
	class StringBuffer
	{
	private:
		std::string m_Data;
		unsigned int m_Position;
		Collections::Stack<unsigned int> m_PositionStack;
	public:
		StringBuffer();
		StringBuffer(std::string data, unsigned int start = 0);

		void Clear();

		void JumpTo(unsigned int position);
		void JumpToStart();
		void JumpToEnd();
		void Step(int ammount = 1);
		inline bool HasEnded() { return m_Position == m_Data.length(); }

		void PushPosition();
		void PopPosition();

		char Get();
		inline std::string GetAll() { return m_Data; }
		std::string GetFrom(int length = -1);
		std::string GetTo(int length = -1);
		std::string GetToFrom(unsigned int start);

		void Add(std::string data);

		std::string Pop();
		std::string PopTo();

		inline unsigned int GetPosition() { return m_Position; }
		inline unsigned int GetLength() { return m_Data.length(); }
	};
}