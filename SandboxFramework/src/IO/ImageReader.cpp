#include "ImageReader.h"

namespace IO
{
	ImageReader::ImageReader(std::string path)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(path.c_str(), 0);
		if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(path.c_str());
		if (fif == FIF_UNKNOWN) return;
		if (FreeImage_FIFSupportsReading(fif)) dib = FreeImage_Load(fif, path.c_str());
		if (!dib)
		{
			m_Success = false;
			return;
		}

		m_Success = true;
	}

	ImageReader::~ImageReader()
	{
		if (!m_Success) return;
		FreeImage_Unload(dib);
	}

	BYTE* ImageReader::GetPixelData(bool premultiplied)
	{
		if (!m_Success) return NULL;
		
		if (premultiplied) FreeImage_PreMultiplyWithAlpha(dib);
		dib = FreeImage_ConvertTo32Bits(dib);
		return convertToRGBA(FreeImage_GetBits(dib));
	}

	unsigned int ImageReader::GetWidth()
	{
		if (!m_Success) return 0;
		return FreeImage_GetWidth(dib);
	}

	unsigned int ImageReader::GetHeight()
	{
		if (!m_Success) return 0;
		return FreeImage_GetHeight(dib);
	}

	BYTE* ImageReader::convertToRGBA(BYTE* data)
	{
		unsigned int w = GetWidth();
		unsigned int h = GetHeight();
		unsigned int p = FreeImage_GetPitch(dib);
		unsigned int bpp = FreeImage_GetBPP(dib);
		BYTE* newData = new BYTE[w * h * 4];
		int i = 0;
		for (int y = 0; y < h; y++) {
			BYTE *pixel = (BYTE*)data;
			for (int x = 0; x < w; x++) {
				newData[i * 4 + 0] = pixel[FI_RGBA_RED];
				newData[i * 4 + 1] = pixel[FI_RGBA_GREEN];
				newData[i * 4 + 2] = pixel[FI_RGBA_BLUE];
				newData[i * 4 + 3] = pixel[FI_RGBA_ALPHA];
				pixel += 4;
				i++;
			}

			data += p;
		}

		return newData;
	}
}