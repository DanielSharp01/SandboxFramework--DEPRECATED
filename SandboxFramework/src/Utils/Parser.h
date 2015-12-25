#pragma once

#include "StringBuffer.h"
#include "../Collections/ArrayList.h"

namespace StringUtils
{
	enum CharType
	{
		Letter,
		Digit,
		Whitespace,
		Symbol
	};

	class Parser
	{
	protected:
		StringBuffer* m_Buffer;
		Collections::ArrayList<std::string> errors;
		unsigned int m_TmpStart;
	public:
		Parser(std::string source);
		~Parser();

		inline StringBuffer* GetBuffer() { return m_Buffer; }
		inline Collections::ArrayList<std::string> GetErrors() { return errors; }

		void JumpTo(unsigned int position);
		void JumpToStart();
		void JumpToEnd();
		void Step(int ammount = 1);
		void StepLength(std::string str);
		inline bool HasEnded() { return m_Buffer->HasEnded(); }

		inline char Get() { return m_Buffer->Get(); }
		CharType GetType();

		void StartTempBuffer();
		StringBuffer RetrieveTempBuffer();
		std::string RetrieveTempString();

		void StepUntil(CharType type);
		void StepUntil(char chr);
		void StepUntilNot(CharType type);
		void StepUntilNot(char chr);
		void StepUntilNot(std::string str, int stopPoint = -1);

		void SignError(std::string error);

	protected:
		bool onString(std::string str, int stopPoint = -1);
	};
}