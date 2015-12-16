#pragma once

#include "GraphicsDevice.h"

namespace SandboxFramework
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

			Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, GLenum imageFormat = GL_RGBA);
			~Texture2D();

			void SetFilters(GLint minFilter, GLint magFilter);
			void Bind();
			void Bind(GLuint slot);
			void Unbind();

			inline GLuint GetWidth() { return m_Width; }
			inline GLuint GetHeight() { return m_Height; }
		};
	}
}