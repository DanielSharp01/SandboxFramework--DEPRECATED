#include "XDocument.h"

#include <iostream>
#include "XMLParser.h"
#include "../IO/FileStream.h"
#include "../IO/StreamReader.h"
#include "../IO/StreamWriter.h"

namespace XML
{
	XDocument::~XDocument()
	{
		delete Root;
	}

	std::string XDocument::ToString()
	{
		std::string ret = "<?xml version = \"1.0\" encoding = \"" + Encoding + "\" ?>\n";
		ret += Root->ToString();
		return ret;
	}
	
	void XDocument::Save(std::string path)
	{
		IO::StreamWriter writer(new IO::FileStream(path, IO::FileAccess::WriteText, IO::FileOpenMode::Create));
		writer.Write(ToString());
		writer.Close();
	}

	XDocument* XDocument::Load(std::string path)
	{
		IO::StreamReader reader(new IO::FileStream(path, IO::FileAccess::ReadText, IO::FileOpenMode::Open));
		std::string src = reader.ReadToEnd();
		reader.Close();
		XMLParser parser(src);
		return parser.Parse();
	}
}