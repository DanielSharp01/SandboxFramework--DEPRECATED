#include "ImageWriter.h"

namespace IO
{
	ImageWriter::ImageWriter(std::string path, BYTE* data, unsigned int width, unsigned int height, unsigned int bpp)
	{
		dib = FreeImage_Allocate(width, height, bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
		unsigned int p = FreeImage_GetPitch(dib);

		BYTE* fdata = FreeImage_GetBits(dib);
		int i = 0;
		for (int y = 0; y < height; y++) {
			BYTE *pixel = (BYTE*)fdata;
			for (int x = 0; x < width; x++) {
				pixel[FI_RGBA_RED] = data[i * 4 + 0];
				pixel[FI_RGBA_GREEN] = data[i * 4 + 1];
				pixel[FI_RGBA_BLUE] = data[i * 4 + 2];
				if (bpp == 32) pixel[FI_RGBA_ALPHA] = data[i * 4 + 3];
				pixel += (bpp == 32 ? 4 : 3);
				i++;
			}

			fdata += p;
		}

		if (bpp == 32) m_Success = FreeImage_Save(FIF_PNG, dib, path.c_str(), PNG_DEFAULT);
		else m_Success = FreeImage_Save(FIF_JPEG, dib, path.c_str(), JPEG_DEFAULT);
	}

	ImageWriter::~ImageWriter()
	{
		FreeImage_Unload(dib);
	}
}