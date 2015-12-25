#pragma once

#include <string>

namespace StringUtils
{
	class StringParser
	{
	private:
		const std::string& m_Stream;
		unsigned int m_Position;
	public:
		StringParser(const std::string& stream);

		void Goto(unsigned int position);
		void Step(int steps);
		void SkipUntilNextLine();
		void SkipString(std::string str);
		void SkipUntilNextNonSpace();
		std::string GetStringUntilNextWhiteSpace();
		std::string GetStringUntilNextCharacter(char chr);

		int GetIntFromString(std::string str) const;
	};
}