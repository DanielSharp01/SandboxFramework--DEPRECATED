#include "Texture2D.h"

#include <iomanip>

typedef unsigned char BYTE;

namespace Sand
{
	namespace Graphics
	{
		Texture2D::Texture2D(GraphicsDevice* graphics, int width, int height)
			: m_Graphics(graphics), m_Width(width), m_Height(height)
		{
			m_Data = new BYTE[width * height * 4];
			memset(m_Data, 0, sizeof(m_Data));

			m_ID = m_Graphics->gl_createTexture2D(NULL, width, height, ImageFormat::RGBA);
			SetFilters(TextureFilter::Nearest, TextureFilter::Nearest);
			m_Refreshable = false;
		}

		Texture2D::Texture2D(GraphicsDevice* graphics, BYTE* data, int width, int height, ImageFormat format)
			: m_Graphics(graphics), m_Width(width), m_Height(height)
		{
			m_Data = data;
			m_ID = m_Graphics->gl_createTexture2D(convertToImageFormat(m_Data, width, height, format), width, height, format);

			SetFilters(TextureFilter::Nearest, TextureFilter::Nearest);
			m_Refreshable = false;
		}

		Texture2D::~Texture2D()
		{
			m_Graphics->gl_destroyTexture2D(this);
			delete m_Data;
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

		void Texture2D::RefreshPixels()
		{
			if (!m_Refreshable) return;
			m_Graphics->gl_refreshPixelData(this);
		}

		void Texture2D::SetData(BYTE* data, GLuint x, GLuint y, GLuint width, GLuint height)
		{
			y = m_Height - y - height;
			m_Graphics->gl_setSubTexture2D(this, data, x, y, width, height);
		}

		BYTE* Texture2D::convertToImageFormat(BYTE* data, unsigned int width, unsigned int height, ImageFormat format)
		{
			BYTE* newData = data;
			if (format == ImageFormat::Red)
			{
				newData = new BYTE[width * height];
				for (int i = 0; i < width * height; i++)
				{
					newData[i] = data[i * 4 + 0];
				}
			}
			else if (format == ImageFormat::Green)
			{
				newData = new BYTE[width * height];
				for (int i = 0; i < width * height; i++)
				{
					newData[i] = data[i * 4 + 1];
				}
			}
			else if (format == ImageFormat::Blue)
			{
				newData = new BYTE[width * height];
				for (int i = 0; i < width * height; i++)
				{
					newData[i] = data[i * 4 + 2];
				}
			}
			else if (format == ImageFormat::RG)
			{
				newData = new BYTE[width * height * 2];
				for (int i = 0; i < width * height; i++)
				{
					newData[i * 2 + 0] = data[i * 4 + 0];
					newData[i * 2 + 1] = data[i * 4 + 1];
				}
			}
			else if (format == ImageFormat::RGB)
			{
				newData = new BYTE[width * height * 3];
				for (int i = 0; i < width * height; i++)
				{
					newData[i * 3 + 0] = data[i * 4 + 0];
					newData[i * 3 + 1] = data[i * 4 + 1];
					newData[i * 3 + 2] = data[i * 4 + 2];
				}
			}
			else if (format == ImageFormat::BGR)
			{
				newData = new BYTE[width * height * 3];
				for (int i = 0; i < width * height; i++)
				{
					newData[i * 3 + 0] = data[i * 4 + 2];
					newData[i * 3 + 1] = data[i * 4 + 1];
					newData[i * 3 + 2] = data[i * 4 + 0];
				}
			}
			else if (format == ImageFormat::BGRA)
			{
				newData = new BYTE[width * height * 4];
				for (int i = 0; i < width * height; i++)
				{
					newData[i * 4 + 0] = data[i * 4 + 2];
					newData[i * 4 + 1] = data[i * 4 + 1];
					newData[i * 4 + 2] = data[i * 4 + 0];
					newData[i * 4 + 3] = data[i * 4 + 3];
				}
			}

			if (newData != data) delete[] data;
			return newData;
		}
	}
}