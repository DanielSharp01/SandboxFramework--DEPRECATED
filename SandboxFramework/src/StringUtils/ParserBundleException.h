#pragma once
#include "../Debug/Exception.h"
#include "ParserException.h"
#include "../Collections/ArrayList.h"

namespace StringUtils {
	class ParserBundleException : public Debug::Exception
	{
	private:
		Collections::ArrayList<ParserException> m_List;
	public:
		void AddException(ParserException exception);
		inline const Collections::ArrayList<ParserException>& GetList() { return m_List; }
		std::string Message() const override;
	};
}