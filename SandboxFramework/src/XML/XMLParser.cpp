#include "XMLParser.h"

using namespace StringUtils;

namespace XML
{
	XMLParser::XMLParser(std::string source)
		: Parser(source) { }

	XDocument* XMLParser::Parse()
	{
		bool rError = false;
		XDocument* ret = new XDocument();

		XElement* xml = parseElement(true);
		if (!xml) rError = true;
		else
		{
			for (int i = 0; i < xml->Attributes.GetCount(); i++)
			{
				if (xml->Attributes[i]->Name == "encoding") ret->Encoding = xml->Attributes[i]->Value;
			}
		}
		StepUntil(CharType::Whitespace);
		ret->Root = parseElement();
		if (!ret->Root) rError = true;
		StepUntil(CharType::Whitespace);
		if (!m_Buffer->HasEnded())
		{
			SignError("And XML document can only have one Root node");
			rError = true;
		}

		if (rError) throw m_Exception;
		return ret;
	}

	XNode* XMLParser::parseNode()
	{
		StepUntil(CharType::Whitespace);
		if (Get() == '<')
		{
			return parseElement();
		}
		else
		{
			return parseTextElement();
		}
	}

	XElement* XMLParser::parseElement(bool canBeXML)
	{
		bool rError = false;
		bool xmlDescriptor = false;
		XElement* ret = new XElement();
		Step();

		if (Get() == '?')
		{
			xmlDescriptor = true;

			if (!canBeXML)
			{
				SignError("<?xml ?> element must be at the start of file");
				rError = true;
			}
			Step();
		}

		if (!(GetType() == CharType::Letter || Get() == '_'))
		{
			if (GetType() == CharType::Symbol || GetType() == CharType::Digit)
			{
				std::string error = "Did not expect \"";
				error += Get();
				error += "\"";
				SignError(error);
				return NULL;
			}
			else //if (GetType() == CharType::Whitespace)
			{
				SignError("Did not expect WHITESPACE");
				return NULL;
			}
		}
		StartTempBuffer();
		while ((GetType() == CharType::Letter || Get() == '_' || GetType() == CharType::Digit) && !HasEnded()) Step();
		ret->Name = RetrieveTempString();

		if (ret->Name != "xml" && xmlDescriptor)
		{
			SignError("\"<?xml\" expected");
			rError = true;
		}

		bool closed = false;
		StepUntil(CharType::Whitespace);
		while (Get() != '>' && Get() != '<' && (Get() != '?' || !xmlDescriptor) && !HasEnded())
		{
			if (Get() == '/')
			{
				closed = true;
				Step();
				if (HasEnded())
				{
					SignError("\">\" expected");
					return NULL;
				}
				else if (Get() != '>')
				{
					std::string error = "Did not expect \"";
					error += Get();
					error += "\"";
					SignError(error);
					SignError("\">\" expected");
					return NULL;
				}
			}
			else if (GetType() == CharType::Letter || Get() == '_')
			{
				XAttribute* attr = parseAttribute();
				ret->Attributes.Add(attr);
				
				if (!attr) rError = true;
				else if (xmlDescriptor)
				{
					if (attr->Name == "version" && attr->Value != "1.0")
					{
						SignError("<?xml version attribute expects value \"1.0\"");
						rError = true;
					}
					else if (attr->Name == "standalone" && attr->Value != "no" && attr->Value != "yes")
					{
						SignError("<?xml standalone attribute expects either value \"yes\" or \"no\"");
						rError = true;
					}
					else if (attr->Name != "version" && attr->Name != "encoding" && attr->Name != "standalone")
					{
						SignError("Invalid <?xml attribute \"" + attr->Name + "\"");
						rError = true;
					}
				}
			}
			else
			{
				std::string error = "Did not expect \"";
				error += Get();
				error += "\"";
				SignError(error);
				Step();
				rError = true;
			}
			StepUntil(CharType::Whitespace);
		}

		if (HasEnded())
		{
			SignError("Tag was not closed");
			if (xmlDescriptor) SignError("\"?>\" expected");
			else SignError("\">\" expected");
			return NULL;
		}
		else if (Get() == '<')
		{
			if (xmlDescriptor) SignError("\"?>\" expected");
			else SignError("\">\" expected");
		}
		else if (Get() == '>' && xmlDescriptor)
		{
			SignError("\"?\" expected");
			return NULL;
		}
		else if (Get() == '?' && xmlDescriptor)
		{
			Step();
			if (HasEnded())
			{
				SignError("Tag was not closed");
				SignError("\">\" expected");
				return NULL;
			}
			else if (Get() != '>')
			{
				SignError("\">\" expected");
				return NULL;
			}
			else
			{
				ret->Name = "?xml";
				closed = true;
				Step();
			}
		}
		else Step();
		if (closed)
		{
			if (rError) return NULL;
			else return ret;
		}

		StepUntil(CharType::Whitespace);
		while (!onString("</", 0) && !HasEnded())
		{
			XNode* node = parseNode();
			ret->Children.Add(node);
			if (!node) rError = true;
			StepUntil(CharType::Whitespace);
		}

		if (HasEnded())
		{
			SignError("Expected </" + ret->Name + ">");
			return NULL;
		}

		Step(2);
		StartTempBuffer();
		while ((GetType() == CharType::Letter || Get() == '_' || GetType() == CharType::Digit) && !HasEnded()) Step();
		std::string name = RetrieveTempString();

		if (name != ret->Name)
		{
			SignError("Expected end tag </" + ret->Name + ">");
			rError = true;
		}

		if (HasEnded())
		{
			SignError("Tag was not closed");
			SignError("\">\" expected");
			return NULL;
		}
		else if (Get() == '<')
		{
			SignError("\">\" expected");
			return NULL;
		}
		else if (Get() != '>')
		{
			while (Get() != '>' && Get() != '<' && !HasEnded())
			{
				std::string error = "Did not expect \"";
				error += Get();
				error += "\"";
				SignError(error);
				Step();
				rError = true;
			}

			if (HasEnded())
			{
				SignError("Tag was not closed");
				SignError("\">\" expected");
				return NULL;
			}
			else if (Get() == '<')
			{
				SignError("\">\" expected");
				return NULL;
			}
			else Step();
		}
		else Step();

		if (!rError) return ret;
		else return NULL;
	}

	XTextElement* XMLParser::parseTextElement()
	{
		XTextElement* ret = new XTextElement();
		ret->Value = "";
		while (Get() != '<' && !m_Buffer->HasEnded())
		{
			if (Get() == '&')
			{
				Step();
				if (onString("lt;", 0))
				{
					Step(3);
					ret->Value += '<';
				}
				else if (onString("gt;", 0))
				{
					Step(3);
					ret->Value += '>';
				}
				else if (onString("amp;"), 0)
				{
					Step(4);
					ret->Value += '&';
				}
				else
				{
					SignError("Undefined &code skipping & symbol");
				}
			}
			else
			{
				ret->Value += Get();
				Step();
			}
		}

		return ret;
	}

	XAttribute* XMLParser::parseAttribute()
	{
		XAttribute* ret = new XAttribute();
		bool rError = false;
		StepUntil(CharType::Whitespace);
		if ((GetType() == CharType::Letter || Get() == '_'))
		{
			StartTempBuffer();
			while ((GetType() == CharType::Letter || Get() == '_' || Get() == ':' || GetType() == CharType::Digit) && !m_Buffer->HasEnded()) Step();
			ret->Name = RetrieveTempString();
			StepUntil(CharType::Whitespace);
		}

		if (HasEnded())
		{
			SignError("Missing attribute value");
			return NULL;
		}

		if (Get() == '=')
		{
			if (ret->Name == "")
			{
				SignError("Missing attribute name");
				Step();
				rError = true;
			}
			else Step();
		}
		else if (GetType() == CharType::Symbol)
		{
			std::string error = "Unexpected symbol \"";
			error += Get();
			error += "\"";
			SignError(error);
			Step();
			return NULL;
		}

		StepUntil(CharType::Whitespace);
		if (HasEnded())
		{
			SignError("Missing attribute value");
			return NULL;
		}

		
		if (Get() == '\"' || Get() == '\'')
		{
			char quote = Get();
			Step();
			StartTempBuffer();
			while (Get() != quote && Get() != '<' && !HasEnded()) Step();

			if (Get() == '<' || HasEnded())
			{
				std::string error = "Expected ";
				error += quote;
				SignError(error);
				return NULL;
			}
			else
			{
				ret->Value = RetrieveTempString();
				Step();
			}
		}
		else
		{
			SignError("Missing attribute value");
			Step();
			rError = true;
		}
		
		if (!rError) return ret;
		else return NULL;
	}
}