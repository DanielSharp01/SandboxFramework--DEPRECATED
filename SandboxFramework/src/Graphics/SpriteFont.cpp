#include "SpriteFont.h"

#include "../XML/XDocument.h"
#include "../XML/XTextElement.h"

namespace Sand
{
	namespace Graphics
	{
		SpriteFont::SpriteFont(Texture2D* texture, int lineHeight)
			: m_Texture(texture), m_LineHeight(lineHeight)
		{
			m_Glyphs = new Collections::Dictionary<char, GlyphMetric*>();
		}

		//TODO: Maybe error report!
		SpriteFont* SpriteFont::Load(Game* game, std::string path)
		{
			using namespace XML;

			XDocument* doc = XDocument::Load(path);
			if (!doc) return NULL;

			XAttribute* attrib = doc->Root->GetAttribute("lineHeight");
			if (!attrib) return NULL;

			int lineHeight = atoi(attrib->Value.c_str()); //TODO: If we ever create a convert class change this
			XElement* element = doc->Root->GetElement("Texture");
			if (!element) return NULL;
			attrib = element->GetAttribute("path");
			if (!attrib) return NULL;
			Texture2D* texture = Texture2D::Load(game, attrib->Value);
			SpriteFont* ret = new SpriteFont(texture, lineHeight);

			element = doc->Root->GetElement("Glyphs");
			if (!element) return NULL;

			Collections::ArrayList<XElement*>* glyphs = element->GetAllElement("Glyph");

			for (int i = 0; i < glyphs->GetCount(); i++)
			{
				XElement* glyph = (*glyphs)[i];

				GlyphMetric* metric = new GlyphMetric();
				XAttribute* attrib = glyph->GetAttribute("char");
				if (!attrib) return NULL;
				char c = (char)atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("textureX");
				if (!attrib) return NULL;
				metric->TextureX = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("textureY");
				if (!attrib) return NULL;
				metric->TextureY = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("offsetX");
				if (!attrib) return NULL;
				metric->OffsetX = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("offsetY");
				if (!attrib) return NULL;
				metric->OffsetY = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("width");
				if (!attrib) return NULL;
				metric->Width = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("height");
				if (!attrib) return NULL;
				metric->Height = atoi(attrib->Value.c_str());
				attrib = glyph->GetAttribute("advanceX");
				if (!attrib) return NULL;
				metric->AdvanceX = atoi(attrib->Value.c_str());

				XElement* kernElement = glyph->GetElement("Kernings");
				if (kernElement)
				{
					Collections::ArrayList<XElement*>* kernings = kernElement->GetAllElement("Kerning");
					for (int i = 0; i < kernings->GetCount(); i++)
					{
						XElement* kerning = (*kernings)[i];

						KerningData kerningData;
						attrib = kerning->GetAttribute("previous");
						if (!attrib) return NULL;
						kerningData.First = (char)atoi(attrib->Value.c_str());
						attrib = kerning->GetAttribute("ammount");
						if (!attrib) return NULL;
						kerningData.Ammount = atoi(attrib->Value.c_str());
						metric->Kerning.Add(kerningData);
					}
					delete kernings;
				}

				ret->AddGlyph(c, metric);
			}
			delete glyphs;

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

		SpriteFont* SpriteFont::CreateFromFont(Game* game, std::string path, unsigned int size, int start, int end)
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
				metric->AdvanceX = face->glyph->advance.x / 64;
				metric->OffsetX = face->glyph->metrics.horiBearingX / 64;
				//Minus because my stupid coordinate system
				metric->OffsetY = -(face->glyph->metrics.horiBearingY) / 64;
				if (FT_HAS_KERNING(face))
				{
					for (int j = start; j < end; j++)
					{
						FT_UInt glyphId = FT_Get_Char_Index(face, i);
						FT_UInt prevGlyphId = FT_Get_Char_Index(face, j);

						FT_Vector delta;
						FT_Get_Kerning(face, prevGlyphId, glyphId, FT_KERNING_DEFAULT, &delta);
						int kerning = delta.x / 64;
						if (kerning != 0) metric->Kerning.Add(KerningData((char)j, kerning));
					}
				}
				tempGlyphs->Add((char)i, metric);

			}

			//Round to nearest power so that we don't have to unpack magic (for now)
			cw--;
			cw = cw | (cw >> 1);
			cw = cw | (cw >> 2);
			cw = cw | (cw >> 4);
			cw = cw | (cw >> 8);
			cw = cw | (cw >> 16);
			cw++;

			ch--;
			ch = ch | (ch >> 1);
			ch = ch | (ch >> 2);
			ch = ch | (ch >> 4);
			ch = ch | (ch >> 8);
			ch = ch | (ch >> 16);
			ch++;

			int ems = end - start;
			int cpr = (int)(sqrt(ems));
			int rows = ems / cpr + (ems % cpr > 0 ? 1 : 0);

			int tw = cw * cpr;
			int th = ch * rows;
			BYTE* newData = new BYTE[tw * th * 4];
			memset(newData, 0, tw * th * 4);

			for (int i = 0; i < ems; i++)
			{
				FT_Load_Char(face, i + start, FT_LOAD_RENDER);
				BYTE* data = face->glyph->bitmap.buffer;
				int h = face->glyph->bitmap.rows;
				int w = face->glyph->bitmap.width;

				int cX = i % cpr;
				int cY = i / cpr;
				int tX = cX * cw;
				int tY = cY * ch;

				(*tempGlyphs)[(char)(i + start)]->TextureX = tX;
				(*tempGlyphs)[(char)(i + start)]->TextureY = tY;

				for (int y = 0; y < h; y++)
				{
					for (int x = 0; x < w; x++)
					{
						int tbX = tX + x;
						int tbY = tY + y;

						//TODO: Option to premultiply
						newData[((th - tbY - 1) * tw + tbX) * 4 + 0] = (255 * data[y * w + x]) / 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 1] = (255 * data[y * w + x]) / 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 2] = (255 * data[y * w + x]) / 255;
						newData[((th - tbY - 1) * tw + tbX) * 4 + 3] = data[y * w + x];
					}
				}
			}

			Texture2D* oglTexture = new Texture2D(game->GetGraphics(), newData, tw, th);

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