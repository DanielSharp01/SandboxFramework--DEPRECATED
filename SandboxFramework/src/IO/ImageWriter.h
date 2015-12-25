#pragma once

#include <string>
#include <FreeImage/FreeImage.h>

namespace IO
{
	class ImageWriter
	{
	private:
		bool m_Success;
		std::string m_Path;
		FIBITMAP *dib;
	public:
		ImageWriter(std::string path, BYTE* data, unsigned int width, unsigned int height, unsigned int bpp);
		~ImageWriter();
	};
}