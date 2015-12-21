#include "Texture2D.h"

typedef unsigned char BYTE;

namespace Sand
{
	namespace Graphics
	{
		Texture2D::Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, ImageFormat imageFormat)
			: m_Graphics(graphics), m_Width(width), m_Height(height)
		{
			m_ID = m_Graphics->gl_createTexture2D(data, width, height, imageFormat);
			SetFilters(TextureFilter::Nearest, TextureFilter::Nearest);
		}

		Texture2D::~Texture2D()
		{
			m_Graphics->gl_destroyTexture2D(this);
		}

		void Texture2D::SetFilters(TextureFilter minFilter, TextureFilter magFilter)
		{
			m_Graphics->gl_setTextureFilters(this, minFilter, magFilter);
		}

		void Texture2D::Bind()
		{
			m_Graphics->gl_bindTexture2D(this);
		}

		void Texture2D::BindToActive(GLuint slot)
		{
			m_Graphics->gl_SetActiveTexture(slot);
			m_Graphics->gl_bindTexture2D(this);
		}

		void Texture2D::Unbind()
		{
			m_Graphics->gl_unbindTexture2D(this);
		}
	}
}