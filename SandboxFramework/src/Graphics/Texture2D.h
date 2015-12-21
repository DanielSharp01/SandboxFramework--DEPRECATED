#pragma once

#include "GraphicsDevice.h"
#include "TextureFilter.h"
#include "ImageFormat.h"

namespace Sand
{
	namespace Graphics
	{
		class SpriteBatch;
		//TODO: Changable BYTE data
		//TODO: Savable to PNG, JPG
		class Texture2D
		{
			friend GraphicsDevice;
			friend SpriteBatch;
		private:
			GraphicsDevice* m_Graphics;
			GLuint m_ID;
			GLuint m_Width;
			GLuint m_Height;
		public:

			Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, ImageFormat imageFormat = ImageFormat::RGBA);
			~Texture2D();

			void SetFilters(TextureFilter minFilter, TextureFilter magFilter);
			void Bind();
			void BindToActive(GLuint slot);
			void Unbind();

			inline GLuint GetWidth() { return m_Width; }
			inline GLuint GetHeight() { return m_Height; }
		};
	}
}