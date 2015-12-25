#pragma once

#include "../Collections/ArrayList.h"
#include "XAttribute.h"
#include "XNode.h"

namespace XML
{
	struct XElement : XNode
	{
		std::string Name;
		Collections::ArrayList<XNode*> Children;
		Collections::ArrayList<XAttribute*> Attributes;

		XElement() = default;
		XElement(std::string name)
			: Name(name) { }

		~XElement()
		{
			for (int i = 0; i < Children.GetCount(); i++)
			{
				delete Children[i];
			}

			for (int i = 0; i < Attributes.GetCount(); i++)
			{
				delete Attributes[i];
			}
		}

		XAttribute* GetAttribute(std::string name)
		{
			for (int i = 0; i < Attributes.GetCount(); i++)
			{
				if (name == Attributes[i]->Name) return Attributes[i];
			}


			return NULL;
		}

		XElement* GetElement(std::string name)
		{
			for (int i = 0; i < Children.GetCount(); i++)
			{
				XElement* element = dynamic_cast<XElement*>(Children[i]);
				if (element && name == element->Name) return element;
			}

			return NULL;
		}

		Collections::ArrayList<XElement*>* GetAllElement(std::string name)
		{
			Collections::ArrayList<XElement*>* ret = new Collections::ArrayList<XElement*>();
			for (int i = 0; i < Children.GetCount(); i++)
			{
				XElement* element = dynamic_cast<XElement*>(Children[i]);
				if (element && name == element->Name) ret->Add(element);
			}

			return ret;
		}

		std::string ToString(std::string spaces = "") override
		{
			std::string ret = spaces + "<" + Name;
			for (int i = 0; i < Attributes.GetCount(); i++)
			{
				ret += " " + Attributes[i]->ToString();
			}
			if (Children.GetCount() == 0)
			{
				ret += " />";
				return ret;
			}

			ret += ">\n";
			for (int i = 0; i < Children.GetCount(); i++)
			{
				ret += Children[i]->ToString(spaces + "   ") + "\n";
			}
			ret += spaces + "</" + Name + ">";
			
			return ret;
		}
	};
}