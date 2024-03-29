#pragma once

#include <string>
#include <FreeImage/FreeImage.h>

namespace IO
{
	class ImageReader
	{
	private:
		bool m_Success;
		FIBITMAP *dib;
	public:
		ImageReader(std::string path);
		~ImageReader();

		BYTE* GetPixelData(bool premultiplied);
		unsigned int GetWidth();
		unsigned int GetHeight();
	private:
		BYTE* convertToRGBA(BYTE* data);
	};
}