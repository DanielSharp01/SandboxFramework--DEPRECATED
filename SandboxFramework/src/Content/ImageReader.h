#pragma once

#include <string>
#include <FreeImage/FreeImage.h>

namespace SandboxFramework
{
	namespace Graphics
	{
		class Texture;
	}

	namespace Content
	{
		class ImageReader
		{
		private:
			bool m_Success;
			FIBITMAP *dib;
		public:
			ImageReader(std::string path);
			~ImageReader();

			BYTE* GetPixelData();
			unsigned int GetWidth();
			unsigned int GetHeight();
		};
	}
}