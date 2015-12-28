#pragma once

#include "../StringUtils/Parser.h"
#include "XDocument.h"
#include "XNode.h"
#include "XElement.h"
#include "XTextElement.h"
#include "XAttribute.h"

namespace XML
{
	class XMLParser : public StringUtils::Parser
	{
	public:
		XMLParser(std::string source);
		XDocument* Parse();
	protected:
		XNode* parseNode();
		XElement* parseElement(bool canBeXML = false);
		XTextElement* parseTextElement();
		XAttribute* parseAttribute();
	};
}