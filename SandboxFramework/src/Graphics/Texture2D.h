#pragma once

#include "GraphicsDevice.h"
#include "TextureFilter.h"
#include "Bitmap.h"

namespace Sand
{
	namespace Graphics
	{
		class SpriteBatch;

		class Texture2D
		{
			friend GraphicsDevice;
			friend SpriteBatch;
		private:
			GraphicsDevice* m_Graphics;
			unsigned int m_ID;
			unsigned short m_Width;
			unsigned short m_Height;
		public:
#ifdef VISUAL_SCHOOL
			Texture2D() {}
#else
			Texture2D() = default;
#endif

			Texture2D(GraphicsDevice* graphics, int width, int height);
			Texture2D(GraphicsDevice* graphics, Bitmap* data);
			~Texture2D();

			static Texture2D* CreateFromBitmap(GraphicsDevice* graphics, Bitmap* bitmap);
			static Texture2D* Texture2D::Load(Game* game, std::string path);
			void SaveAsJPG(std::string path);
			void SaveAsPNG(std::string path);

			void SetFilters(TextureFilter minFilter, TextureFilter magFilter);
			void Bind();
			void BindToActive(unsigned short slot);
			void Unbind();

			void SetData(Bitmap* bitmap);
			void SetSubData(Bitmap* bitmap, unsigned short x, unsigned short y);
			Bitmap* GetBitmap();
			inline unsigned short GetWidth() { return m_Width; }
			inline unsigned short GetHeight() { return m_Height; }
		};
	}
}