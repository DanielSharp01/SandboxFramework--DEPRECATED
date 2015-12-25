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
			SignError("And XML document can only have one Root node at " + std::to_string(m_Buffer->GetPosition()));
			rError = true;
		}

		ret->Errors = errors;

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
				std::string error = "<?xml ?> element must be at the start of file at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
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
				error += "\" at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				return NULL;
			}
			else //if (GetType() == CharType::Whitespace)
			{
				std::string error = "Did not expect WHITESPACE at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				return NULL;
			}
		}
		StartTempBuffer();
		while ((GetType() == CharType::Letter || Get() == '_' || GetType() == CharType::Digit) && !HasEnded()) Step();
		Step(-1);
		ret->Name = RetrieveTempString();
		Step();

		if (ret->Name != "xml" && xmlDescriptor)
		{
			std::string error = "\"<?xml\" expected" + std::to_string(m_Buffer->GetPosition());
			SignError(error);
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
					SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
					return NULL;
				}
				else if (Get() != '>')
				{
					std::string error = "Did not expect \"";
					error += Get();
					error += "\" at position " + std::to_string(m_Buffer->GetPosition());
					SignError(error);
					SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
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
						std::string error = "<?xml version attribute expects value \"1.0\"" + std::to_string(m_Buffer->GetPosition());
						SignError(error);
						rError = true;
					}
					else if (attr->Name == "standalone" && attr->Value != "no" && attr->Value != "yes")
					{
						std::string error = "<?xml standalone attribute expects either value \"yes\" or \"no\"" + std::to_string(m_Buffer->GetPosition());
						SignError(error);
						rError = true;
					}
					else if (attr->Name != "version" && attr->Name != "encoding" && attr->Name != "standalone")
					{
						std::string error = "invalid <?xml attribute \"" + attr->Name + "\"" + std::to_string(m_Buffer->GetPosition());
						SignError(error);
						rError = true;
					}
				}
			}
			else
			{
				std::string error = "Did not expect \"";
				error += Get();
				error += "\" at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				Step();
				rError = true;
			}
			StepUntil(CharType::Whitespace);
		}

		if (HasEnded())
		{
			SignError("Tag was not closed " + std::to_string(m_Buffer->GetPosition()));
			if (xmlDescriptor) SignError("\"?>\" expected at " + std::to_string(m_Buffer->GetPosition()));
			else SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
			return NULL;
		}
		else if (Get() == '<')
		{
			if (xmlDescriptor) SignError("\"?>\" expected at " + std::to_string(m_Buffer->GetPosition()));
			else SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
		}
		else if (Get() == '>' && xmlDescriptor)
		{
			SignError("\"?\" expected at " + std::to_string(m_Buffer->GetPosition()));
			return NULL;
		}
		else if (Get() == '?' && xmlDescriptor)
		{
			Step();
			if (HasEnded())
			{
				SignError("Tag was not closed " + std::to_string(m_Buffer->GetPosition()));
				SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
				return NULL;
			}
			else if (Get() != '>')
			{
				SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
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
			SignError("Expected </" + ret->Name + "> at " + std::to_string(m_Buffer->GetPosition()));
			return NULL;
		}

		Step(2);
		StartTempBuffer();
		while ((GetType() == CharType::Letter || Get() == '_' || GetType() == CharType::Digit) && !HasEnded()) Step();
		Step(-1);
		std::string name = RetrieveTempString();
		Step(1);

		if (name != ret->Name)
		{
			SignError("Expected end tag </" + ret->Name + "> at " + std::to_string(m_Buffer->GetPosition()));
			rError = true;
		}

		if (HasEnded())
		{
			SignError("Tag was not closed " + std::to_string(m_Buffer->GetPosition()));
			SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
			return NULL;
		}
		else if (Get() == '<')
		{
			SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
			return NULL;
		}
		else if (Get() != '>')
		{
			while (Get() != '>' && Get() != '<' && !HasEnded())
			{
				std::string error = "Did not expect \"";
				error += Get();
				error += "\" at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				Step();
				rError = true;
			}

			if (HasEnded())
			{
				SignError("Tag was not closed " + std::to_string(m_Buffer->GetPosition()));
				SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
				return NULL;
			}
			else if (Get() == '<')
			{
				SignError("\">\" expected at " + std::to_string(m_Buffer->GetPosition()));
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
					SignError("Undefined &code skipping & symbol at " + std::to_string(m_Buffer->GetPosition()));
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
			Step(-1);
			ret->Name = RetrieveTempString();
			Step(1);
			StepUntil(CharType::Whitespace);
		}

		if (HasEnded())
		{
			std::string error = "Missing attribute value at position " + std::to_string(m_Buffer->GetPosition());
			SignError(error);
			return NULL;
		}

		if (Get() == '=')
		{
			if (ret->Name == "")
			{
				std::string error = "Missing attribute name at position " + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				Step();
				rError = true;
			}
			else Step();
		}
		else if (GetType() == CharType::Symbol)
		{
			std::string error = "Unexpected symbol \"";
			error += Get();
			error += "\" at position " + std::to_string(m_Buffer->GetPosition());
			SignError(error);
			Step();
			return NULL;
		}

		StepUntil(CharType::Whitespace);
		if (HasEnded())
		{
			std::string error = "Missing attribute value at position " + std::to_string(m_Buffer->GetPosition());
			SignError(error);
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
				error += " at position" + std::to_string(m_Buffer->GetPosition());
				SignError(error);
				return NULL;
			}
			else
			{
				Step(-1);
				ret->Value = RetrieveTempString();
				Step(2);
			}
		}
		else
		{
			std::string error = "Missing attribute value at position " + std::to_string(m_Buffer->GetPosition());
			SignError(error);
			Step();
			rError = true;
		}
		
		if (!rError) return ret;
		else return NULL;
	}
}