#include "ImageReader.h"

namespace SandboxFramework
{
	namespace Content
	{
		ImageReader::ImageReader(std::string path)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			BYTE* bits;
			unsigned int width, height;

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

		BYTE* ImageReader::GetPixelData()
		{
			if (!m_Success) return NULL;

			return FreeImage_GetBits(dib);
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
	}
}