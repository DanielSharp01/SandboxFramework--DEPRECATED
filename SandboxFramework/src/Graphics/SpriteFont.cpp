#include "SpriteFont.h"

#include "../StringUtils/Parser.h"
#include "../StringUtils/Convert.h"
#include "../XML/XDocument.h"
#include "../XML/XTextElement.h"

namespace Sand
{
	namespace Graphics
	{
		SpriteFont::SpriteFont()
			: m_Texture(NULL), m_LineHeight(0)
		{
			m_Glyphs = new Collections::Dictionary<char, GlyphMetric*>();
		}

		SpriteFont::SpriteFont(Texture2D* texture, int lineHeight)
			: m_Texture(texture), m_LineHeight(lineHeight)
		{
			m_Glyphs = new Collections::Dictionary<char, GlyphMetric*>();
		}

		SpriteFont* SpriteFont::Load(Game* game, std::string path)
		{
			using namespace XML;
			using namespace StringUtils;

			SpriteFont* ret = new SpriteFont();
			ParserBundleException exceptions;
			XDocument* doc = XDocument::Load(path);
			if (!doc) return NULL;

			XAttribute* attrib = doc->Root->GetAttribute("lineHeight");
			if (attrib)
			{
				if (!Convert::ToUnsignedInt(attrib->Value, ret->m_LineHeight))
					exceptions.AddException(ParserException("Expected unsigned integer value for \"lineHeight\" attribute", 0, 0));
			}
			else exceptions.AddException(ParserException("Expected \"lineHeight\" attribute in ROOT element!", 0, 0));

			XElement* element = doc->Root->GetElement("Texture");
			if (element)
			{
				attrib = element->GetAttribute("path");
				if (attrib) ret->m_Texture = Texture2D::Load(game, attrib->Value);
				else exceptions.AddException(ParserException("Expected \"path\" attribute in element \"Texture\"!", 0, 0));
			}
			else exceptions.AddException(ParserException("Expected \"Texture\" element!", 0, 0));

			element = doc->Root->GetElement("Glyphs");
			if (element)
			{
				for (int i = 0; i < element->Children.GetCount(); i++)
				{
					XElement* glyph = dynamic_cast<XElement*>(element->Children[i]);

					if (glyph && glyph->Name == "Glyph")
					{
						GlyphMetric* metric = new GlyphMetric();
						char c = '\0';
						XAttribute* attrib = glyph->GetAttribute("char");
						if (attrib)
						{
							unsigned int out = 0;
							if (Convert::ToUnsignedInt(attrib->Value, out)) c = (char)out;
							else exceptions.AddException(ParserException("Expected unsigned integer value for \"char\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"char\" attribute in \"Glyph\" element", 0, 0));
						
						attrib = glyph->GetAttribute("textureX");
						if (attrib)
						{
							if (!Convert::ToUnsignedInt(attrib->Value, metric->TextureX))
								exceptions.AddException(ParserException("Expected unsigned integer value for \"textureX\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"textureX\" attribute in \"Glyph\" element", 0, 0));
						
						attrib = glyph->GetAttribute("textureY");
						if (attrib)
						{
							if (!Convert::ToUnsignedInt(attrib->Value, metric->TextureY))
								exceptions.AddException(ParserException("Expected unsigned integer value for \"textureY\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"textureY\" attribute in \"Glyph\" element", 0, 0));
						
						attrib = glyph->GetAttribute("offsetX");
						if (attrib)
						{
							if (!Convert::ToInt(attrib->Value, metric->OffsetX))
								exceptions.AddException(ParserException("Expected integer value for \"offsetX\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"offsetX\" attribute in \"Glyph\" element", 0, 0));
						
						attrib = glyph->GetAttribute("offsetY");
						if (attrib)
						{
							if (!Convert::ToInt(attrib->Value, metric->OffsetY))
								exceptions.AddException(ParserException("Expected integer value for \"offsetY\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"offsetY\" attribute in \"Glyph\" element", 0, 0));
						
						attrib = glyph->GetAttribute("width");
						if (attrib)
						{
							if (!Convert::ToUnsignedInt(attrib->Value, metric->Width))
								exceptions.AddException(ParserException("Expected unsigned integer value for \"width\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"width\" attribute in \"Glyph\" element", 0, 0));

						attrib = glyph->GetAttribute("height");
						if (attrib)
						{
							if (!Convert::ToUnsignedInt(attrib->Value, metric->Height))
								exceptions.AddException(ParserException("Expected unsigned integer value for \"height\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"height\" attribute in \"Glyph\" element", 0, 0));

						attrib = glyph->GetAttribute("advanceX");
						if (attrib)
						{
							if (!Convert::ToInt(attrib->Value, metric->AdvanceX))
								exceptions.AddException(ParserException("Expected integer value for \"advanceX\" attribute", 0, 0));
						}
						else exceptions.AddException(ParserException("Expected \"advanceX\" attribute in \"Glyph\" element", 0, 0));

						for (int i = 0; i < glyph->Children.GetCount(); i++)
						{
							XElement* kernElement = dynamic_cast<XElement*>(glyph->Children[i]);
							if (kernElement && kernElement->Name == "Kernings")
							{
								for (int i = 0; i < kernElement->Children.GetCount(); i++)
								{
									XElement* kerning = dynamic_cast<XElement*>(kernElement->Children[i]);

									if (kerning && kerning->Name == "Kerning")
									{
										KerningData kerningData;
										attrib = kerning->GetAttribute("previous");
										if (attrib)
										{
											unsigned int out = 0;
											if (Convert::ToUnsignedInt(attrib->Value, out)) kerningData.First = (char)out;
											else exceptions.AddException(ParserException("Expected unsigned integer value for \"previous\" attribute", 0, 0));
										}
										else exceptions.AddException(ParserException("Expected \"previous\" attribute in \"Kerning\" element", 0, 0));
										attrib = kerning->GetAttribute("ammount");
										if (attrib)
										{
											if (!Convert::ToInt(attrib->Value, kerningData.Ammount))
												exceptions.AddException(ParserException("Expected integer value for \"ammount\" attribute", 0, 0));
										}
										else exceptions.AddException(ParserException("Expected \"ammount\" attribute in \"Kerning\" element", 0, 0));
										metric->Kerning.Add(kerningData);
									}
									else
									{
										if (kerning) exceptions.AddException(ParserException("Unexpected \"" + kerning->Name + "\" element in \"Kernings\" element", 0, 0));
										else exceptions.AddException(ParserException("Unexpected TEXT element in \"Kernings\" element", 0, 0));
									}
								}
							}
							else
							{
								if (kernElement) exceptions.AddException(ParserException("Unexpected \"" + kernElement->Name + "\" element in \"Glyph\" element", 0, 0));
								else exceptions.AddException(ParserException("Unexpected TEXT element in \"Glyph\" element", 0, 0));
							}
						}

						if (!ret->m_Glyphs->ContainsKey(c)) ret->AddGlyph(c, metric);
						else exceptions.AddException(ParserException("Glyph with character id \"" + std::to_string((int)c) + "\" was included more than once", 0, 0));
					}
					else
					{
						if (glyph) exceptions.AddException(ParserException("Unexpected \"" + glyph->Name + "\" element in \"Glyphs\" element", 0, 0));
						else exceptions.AddException(ParserException("Unexpected TEXT element in \"Glyphs\" element", 0, 0));
					}
				}
			}
			else exceptions.AddException(ParserException("Expected \"Glyphs\" element!", 0, 0));

			if (exceptions.GetList().GetCount() > 0) throw exceptions;
			return ret;
		}
		
		void SpriteFont::Save(std::string path)
		{
			using namespace XML;
			std::string texturePath = path.substr(0, path.find_last_of('.')) + ".png";
			XDocument* doc = new XDocument();

			doc->Encoding = "UTF-8";
			doc->Root = new XElement("SpriteFont");
			doc->Root->Attributes.Add(new XAttribute("lineHeight", std::to_string(m_LineHeight)));
			XElement* tex = new XElement("Texture");
			tex->Attributes.Add(new XAttribute("path", texturePath));
			doc->Root->Children.Add(tex);
			XElement* glyphs = new XElement("Glyphs");
			
			for (int i = 0; i < m_Glyphs->GetCount(); i++)
			{
				char c = (*m_Glyphs->GetKeys())[i];
				GlyphMetric* metric = (*m_Glyphs->GetValues())[i];
				XElement* glyph = new XElement("Glyph");
				glyph->Attributes.Add(new XAttribute("char", std::to_string((int)c)));
				glyph->Attributes.Add(new XAttribute("textureX", std::to_string(metric->TextureX)));
				glyph->Attributes.Add(new XAttribute("textureY", std::to_string(metric->TextureY)));
				glyph->Attributes.Add(new XAttribute("offsetX", std::to_string(metric->OffsetX)));
				glyph->Attributes.Add(new XAttribute("offsetY", std::to_string(metric->OffsetY)));
				glyph->Attributes.Add(new XAttribute("width", std::to_string(metric->Width)));
				glyph->Attributes.Add(new XAttribute("height", std::to_string(metric->Height)));
				glyph->Attributes.Add(new XAttribute("advanceX", std::to_string(metric->AdvanceX)));
				XElement* kernings = new XElement("Kernings");
				
				for (int i = 0; i < metric->Kerning.GetCount(); i++)
				{
					KerningData kerningData = metric->Kerning[i];
					XElement* kerning = new XElement("Kerning");
					kerning->Attributes.Add(new XAttribute("previous", std::to_string((int)kerningData.First)));
					kerning->Attributes.Add(new XAttribute("ammount", std::to_string(kerningData.Ammount)));
					kernings->Children.Add(kerning);
				}

				if (kernings->Children.GetCount() > 0) glyph->Children.Add(kernings);
				glyphs->Children.Add(glyph);
			}

			doc->Root->Children.Add(glyphs);
			
			doc->Save(path);
			m_Texture->SaveAsPNG(texturePath);
			delete doc;
		}

		SpriteFont* SpriteFont::CreateFromFont(Game* game, std::string path, unsigned int size, int start, int end, bool premultiplied)
		{
			FT_Face face;
			FT_New_Face(game->GetFreeType(), path.c_str(), 0, &face);
			FT_Set_Pixel_Sizes(face, 0, size);
			int cw = 0;
			int ch = 0;

			Collections::Dictionary<char, GlyphMetric*>* tempGlyphs = new Collections::Dictionary<char, GlyphMetric*>();

			for (int i = start; i < end; i++)
			{
				FT_Load_Char(face, i, FT_LOAD_RENDER);
				
				int w = face->glyph->bitmap.width;
				int h = face->glyph->bitmap.rows;

				if (cw < w) cw = w;
				if (ch < h) ch = h;

				GlyphMetric* metric = new GlyphMetric();

				metric->Width = w;
				metric->Height = h;
				metric->AdvanceX = face->glyph->advance.x >> 6;
				metric->OffsetX = face->glyph->metrics.horiBearingX >> 6;
				//Minus because my stupid coordinate system
				metric->OffsetY = -(face->glyph->metrics.horiBearingY) >> 6;
				if (FT_HAS_KERNING(face))
				{
					for (int j = start; j < end; j++)
					{
						FT_UInt glyphId = FT_Get_Char_Index(face, i);
						FT_UInt prevGlyphId = FT_Get_Char_Index(face, j);

						FT_Vector delta;
						FT_Get_Kerning(face, prevGlyphId, glyphId, FT_KERNING_DEFAULT, &delta);
						int kerning = delta.x >> 6;
						if (kerning != 0) metric->Kerning.Add(KerningData((char)j, kerning));
					}
				}
				tempGlyphs->Add((char)i, metric);

			}

			int ems = end - start;
			int cpr = (int)(sqrt(ems));
			int rows = ems / cpr + (ems % cpr > 0 ? 1 : 0);

			int tw = cw * cpr;
			int th = ch * rows;
			BYTE* newData = new BYTE[tw * th * 4];
			memset(newData, 0, tw * th * 4 * sizeof(BYTE));

			for (int i = 0; i < ems; i++)
			{
				FT_Load_Char(face, i + start, FT_LOAD_RENDER);
				BYTE* data = face->glyph->bitmap.buffer;
				int h = face->glyph->bitmap.rows;
				int w = face->glyph->bitmap.width;

				int tX = (i % cpr) * cw;
				int tY = (i / cpr) * ch;

				(*tempGlyphs)[(char)(i + start)]->TextureX = tX;
				(*tempGlyphs)[(char)(i + start)]->TextureY = tY;

				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						int tbX = tX + x;
						int tbY = tY + y;

						newData[((th - tbY - 1) * tw + tbX) * 4 + 0] = 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 1] = 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 2] = 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 3] = data[y * w + x];
					}
				}
			}

			Bitmap* bitmap = new Bitmap(newData, tw, th, ImageFormat::RGBA);
			if (premultiplied) bitmap->Premultiply();
			Texture2D* oglTexture = new Texture2D(game->GetGraphics(), bitmap);
			delete bitmap;
			SpriteFont* spriteFont = new SpriteFont(oglTexture, size);
			delete spriteFont->m_Glyphs;
			spriteFont->m_Glyphs = tempGlyphs;
			return spriteFont;
		}

		void SpriteFont::AddGlyph(char character, GlyphMetric* metric)
		{
			m_Glyphs->Add(character, metric);
		}

		Math::Rectangle SpriteFont::GetSource(char character)
		{
			GlyphMetric* glyph = (*m_Glyphs)[character];
			return Math::Rectangle(glyph->TextureX, glyph->TextureY, glyph->Width, glyph->Height);
		}

		Math::Rectangle SpriteFont::GetDestination(char character)
		{
			GlyphMetric* glyph = (*m_Glyphs)[character];
			return Math::Rectangle(0, 0, glyph->Width, glyph->Height);
		}

		Math::Vector2 SpriteFont::GetOffset(char previous, char character)
		{
 			GlyphMetric* glyph = (*m_Glyphs)[character];
			Math::Vector2 kerning(0, 0);
			if (previous != '\0')
			{
				for (int i = 0; i < glyph->Kerning.GetCount(); i++)
				{
					if (glyph->Kerning[i].First == character)
					{
						kerning = Math::Vector2(glyph->Kerning[i].Ammount, 0);
						break;
					}
				}
			}

			return kerning + Math::Vector2(glyph->OffsetX, glyph->OffsetY);
		}

		float SpriteFont::GetAdvanceX(char character)
		{
			return (*m_Glyphs)[character]->AdvanceX;
		}

		Math::Vector2 SpriteFont::MeasureText(std::string text)
		{
			Math::Vector2 size(0, 0);
			Math::Vector2 pos(0, 0);

			char last = '\0';
			for (int i = 0; i < text.length(); i++)
			{
				char c = text[i];
				if (c != '\n')
				{
					pos.X += GetAdvanceX(c);
				}
				else
				{
					if (pos.X > size.X) size.X = pos.X;
					pos.X = 0;
					pos.Y += GetLineHeight();
				}

				last = c;
			}

			if (pos.X > size.X) size.X = pos.X;
			size.Y = pos.Y + GetLineHeight();

			return size;
		}
	}
}