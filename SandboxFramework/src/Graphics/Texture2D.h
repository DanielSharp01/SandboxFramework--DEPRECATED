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
			BYTE* m_Data;
			bool m_Refreshable;
		public:

			Texture2D() = default;
			Texture2D(GraphicsDevice* graphics, int width, int height);
			Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, ImageFormat format = ImageFormat::RGBA);
			~Texture2D();

			static Texture2D* CreateFromImage(GraphicsDevice* graphics, std::string path, bool premultiplied, ImageFormat format = ImageFormat::RGBA);
			static Texture2D* Texture2D::Load(Game* game, std::string path);
			void SaveAsJPG(std::string filename);

			void SaveAsPNG(std::string filename);

			void SetFilters(TextureFilter minFilter, TextureFilter magFilter);
			void Bind();
			void BindToActive(GLuint slot);
			void Unbind();
			void RefreshPixels();
			void SetData(BYTE* data, GLuint x, GLuint y, GLuint width, GLuint height);

			inline BYTE* GetData() { return m_Data; }
			inline GLuint GetWidth() { return m_Width; }
			inline GLuint GetHeight() { return m_Height; }
		private:
			BYTE* convertToImageFormat(BYTE* data, unsigned int width, unsigned int height, ImageFormat format);
		};
	}
}