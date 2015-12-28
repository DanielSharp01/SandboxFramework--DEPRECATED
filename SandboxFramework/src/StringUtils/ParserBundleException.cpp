#include "ParserBundleException.h"

namespace StringUtils {
	void ParserBundleException::AddException(ParserException exception)
	{
		m_List.Add(exception);
	}
		
	std::string ParserBundleException::Message() const
	{
		return "Parser encountered errors, see GetList() for details!";
	}
}