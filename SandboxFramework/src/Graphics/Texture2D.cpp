#include "Texture2D.h"

namespace Sand
{
	namespace Graphics
	{
		Texture2D::Texture2D(GraphicsDevice* graphics, int width, int height)
			: m_Graphics(graphics), m_Width(width), m_Height(height)
		{
			m_ID = m_Graphics->gl_createTexture2D(NULL, width, height, ImageFormat::RGBA);
			SetFilters(TextureFilter::Nearest, TextureFilter::Nearest);
		}

		Texture2D::Texture2D(GraphicsDevice* graphics, Bitmap* bitmap)
			: m_Graphics(graphics), m_Width(bitmap->GetWidth()), m_Height(bitmap->GetHeight())
		{
			m_ID = m_Graphics->gl_createTexture2D(bitmap->GetBytes(), bitmap->GetWidth(), bitmap->GetHeight(), bitmap->GetFormat());
			SetFilters(TextureFilter::Nearest, TextureFilter::Nearest);
		}

		Texture2D::~Texture2D()
		{
			m_Graphics->gl_destroyTexture2D(this);
		}

		Texture2D* Texture2D::CreateFromBitmap(GraphicsDevice* graphics, Bitmap* bitmap)
		{
			return new Texture2D(graphics, bitmap);
		}

		Texture2D* Texture2D::Load(Game* game, std::string path)
		{
			Bitmap* bmp = Bitmap::Load(path, true);
			Texture2D* ret = Texture2D::CreateFromBitmap(game->GetGraphics(), bmp);
			delete bmp;
			return ret;
		}

		void Texture2D::SaveAsJPG(std::string path)
		{
			Bitmap* bmp = GetBitmap();
			bmp->SaveAsJPG(path);
			delete bmp;
		}

		void Texture2D::SaveAsPNG(std::string path)
		{
			Bitmap* bmp = GetBitmap();
			bmp->SaveAsPNG(path);
			delete bmp;
		}

		void Texture2D::SetFilters(TextureFilter minFilter, TextureFilter magFilter)
		{
			m_Graphics->gl_setTextureFilters(this, minFilter, magFilter);
		}

		void Texture2D::Bind()
		{
			m_Graphics->gl_bindTexture2D(this);
		}

		void Texture2D::BindToActive(unsigned short slot)
		{
			m_Graphics->gl_SetActiveTexture(slot);
			m_Graphics->gl_bindTexture2D(this);
		}

		void Texture2D::Unbind()
		{
			m_Graphics->gl_unbindTexture2D(this);
		}

		Bitmap* Texture2D::GetBitmap()
		{
			return m_Graphics->gl_getTexture2DAsBitmap(this);
		}

		void Texture2D::SetData(Bitmap* bitmap)
		{
			m_Graphics->gl_setTexture2D(this, bitmap->GetBytes(), bitmap->GetWidth(), bitmap->GetHeight(), bitmap->GetFormat());
		}

		void Texture2D::SetSubData(Bitmap* bitmap, unsigned short x, unsigned short y)
		{
			y = m_Height - y - bitmap->GetHeight();
			m_Graphics->gl_setSubTexture2D(this, bitmap->GetBytes(), x, y, bitmap->GetWidth(), bitmap->GetHeight(), bitmap->GetFormat());
		}
	}
}