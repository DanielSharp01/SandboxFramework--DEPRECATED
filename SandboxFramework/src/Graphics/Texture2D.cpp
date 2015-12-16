#include "Texture2D.h"

typedef unsigned char BYTE;

namespace SandboxFramework
{
	namespace Graphics
	{
		Texture2D::Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, GLenum imageFormat)
			: m_Graphics(graphics), m_Width(width), m_Height(height)
		{
			m_ID = m_Graphics->gl_createTexture2D(data, width, height, imageFormat);
			SetFilters(GL_NEAREST, GL_NEAREST);
		}

		Texture2D::~Texture2D()
		{
			m_Graphics->gl_destroyTexture2D(this);
		}

		void Texture2D::SetFilters(GLint minFilter, GLint magFilter)
		{
			m_Graphics->gl_setTextureFilters(this, minFilter, magFilter);
		}

		void Texture2D::Bind()
		{
			m_Graphics->gl_bindTexture2D(this);
		}

		void Texture2D::Bind(GLuint slot)
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