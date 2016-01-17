#pragma once

#include "../Collections/Dictionary.h"
#include "Texture2D.h"

namespace Sand
{
	namespace Graphics
	{
		struct KerningData
		{
			char First;
			int Ammount;

#ifdef VISUAL_SCHOOL
			KerningData() {}
#else
			KerningData() = default;
#endif

			KerningData(char first, int ammount)
				: First(first), Ammount(ammount)
			{ }
		};

		struct GlyphMetric
		{
			int TextureX;
			int TextureY;
			int OffsetX;
			int OffsetY;
			int Width;
			int Height;
			int AdvanceX;

			Collections::ArrayList<KerningData> Kerning;
		};

		class SpriteFont
		{
		private:
			Texture2D* m_Texture;
			int m_LineHeight;

			Collections::Dictionary<char, GlyphMetric*>* m_Glyphs;
		public:
			SpriteFont();
			SpriteFont(Texture2D* texture, int lineHeight);

			static SpriteFont* Load(Game* game, std::string path);
			static SpriteFont* CreateFromFont(Game* game, std::string path, unsigned int size, int start = 32, int end = 128, bool premultiplied = true);
			void Save(std::string path);

			void AddGlyph(char character, GlyphMetric* metric);

			inline Texture2D* GetTexture() { return m_Texture; }
			inline int GetLineHeight() { return m_LineHeight; }

			Math::Rectangle GetSource(char character);
			Math::Rectangle GetDestination(char character);
			Math::Vector2 GetOffset(char previous, char character);
			float GetAdvanceX(char character);
			Math::Vector2 MeasureText(std::string text);
		};
	}
}