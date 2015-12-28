#include "Bitmap.h"

#include "../IO/ImageWriter.h"
#include "../IO/ImageReader.h"

namespace Sand
{
	namespace Graphics
	{
		Bitmap::Bitmap(BYTE* bytes, unsigned short width, unsigned short height, ImageFormat format)
			: m_Bytes(bytes), m_Width(width), m_Height(height), m_Format(format)
		{ }
		
		Bitmap::~Bitmap()
		{
			delete[] m_Bytes;
		}

		Bitmap* Bitmap::Load(std::string path, bool premultiplied)
		{
			IO::ImageReader reader(path);
			return new Bitmap(reader.GetPixelData(premultiplied), reader.GetWidth(), reader.GetHeight());
		}

		void Bitmap::SaveAsPNG(std::string path)
		{
			BYTE* bytes = GetCopyOfBytes(ImageFormat::RGBA);
			IO::ImageWriter writer(path, m_Bytes, m_Width, m_Height, 32);
		}

		void Bitmap::SaveAsJPG(std::string path)
		{
			BYTE* bytes = GetCopyOfBytes(ImageFormat::RGB);
			IO::ImageWriter writer(path, bytes, m_Width, m_Height, 24);
		}

		void Bitmap::Premultiply()
		{
			if (getPixelStride() != 4)
			{
				memset(m_Bytes, 0, m_Width * m_Height * getPixelStride() * sizeof(BYTE));
				return;
			}

			for (int i = 0; i < m_Width * m_Height; i++)
			{
				m_Bytes[i * 4 + (m_Format == ImageFormat::RGBA ? 0 : 2)] = (m_Bytes[i * 4 + (m_Format == ImageFormat::RGBA ? 0 : 2)] * m_Bytes[i * 4 + 3] + 127) / 255;
				m_Bytes[i * 4 + 1] = (m_Bytes[i * 4 + 1] * m_Bytes[i * 4 + 3] + 127) / 255;
				m_Bytes[i * 4 + (m_Format == ImageFormat::RGBA ? 2 : 0)] = (m_Bytes[i * 4 + (m_Format == ImageFormat::RGBA ? 2 : 0)] * m_Bytes[i * 4 + 3] + 127) / 255;
			}
		}

		BYTE* Bitmap::GetCopyOfBytes(ImageFormat format)
		{
			BYTE* newBytes;
			if (format == ImageFormat::Red)
			{
				newBytes = new BYTE[m_Width * m_Height];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i] = getRed(i);
				}
			}
			else if (format == ImageFormat::Green)
			{
				newBytes = new BYTE[m_Width * m_Height];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i] = getGreen(i);
				}
			}
			else if (format == ImageFormat::Blue)
			{
				newBytes = new BYTE[m_Width * m_Height];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i] = getBlue(i);
				}
			}
			else if (format == ImageFormat::RG)
			{
				newBytes = new BYTE[m_Width * m_Height * 2];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i * 2 + 0] = getRed(i);
					newBytes[i * 2 + 1] = getGreen(i);
				}
			}
			else if (format == ImageFormat::RGB)
			{
				newBytes = new BYTE[m_Width * m_Height * 3];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i * 3 + 0] = getRed(i);
					newBytes[i * 3 + 1] = getGreen(i);
					newBytes[i * 3 + 2] = getBlue(i);
				}
			}
			else if (format == ImageFormat::BGR)
			{
				newBytes = new BYTE[m_Width * m_Height * 3];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i * 3 + 0] = getBlue(i);
					newBytes[i * 3 + 1] = getGreen(i);
					newBytes[i * 3 + 2] = getRed(i);
				}
			}
			else if (format == ImageFormat::BGRA)
			{
				newBytes = new BYTE[m_Width * m_Height * 4];
				for (int i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i * 4 + 0] = getBlue(i);
					newBytes[i * 4 + 1] = getGreen(i);
					newBytes[i * 4 + 2] = getRed(i);
					newBytes[i * 4 + 3] = getAlpha(i);
				}
			}
			else //if (format == ImageFormat::RGBA)
			{
				newBytes = new BYTE[m_Width * m_Height * 4];
				for (unsigned short i = 0; i < m_Width * m_Height; i++)
				{
					newBytes[i * 4 + 0] = getRed(i);
					newBytes[i * 4 + 1] = getGreen(i);
					newBytes[i * 4 + 2] = getBlue(i);
					newBytes[i * 4 + 3] = getAlpha(i);
				}
			}

			return newBytes;
		}

		BYTE Bitmap::getRed(int i)
		{
			if (m_Format == ImageFormat::Red)
			{
				return m_Bytes[i];
			}
			else if (m_Format == ImageFormat::Green)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Blue)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::RG)
			{
				return m_Bytes[i * 2 + 0];
			}
			else if (m_Format == ImageFormat::RGB)
			{
				return m_Bytes[i * 3 + 0];
			}
			else if (m_Format == ImageFormat::BGR)
			{
				return m_Bytes[i * 3 + 2];
			}
			else if (m_Format == ImageFormat::BGRA)
			{
				return m_Bytes[i * 4 + 2];
			}
			else //if (m_Format == ImageFormat::RGBA)
			{
				return m_Bytes[i * 4 + 0];
			}
		}

		BYTE Bitmap::getGreen(int i)
		{
			if (m_Format == ImageFormat::Red)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Green)
			{
				return m_Bytes[i];
			}
			else if (m_Format == ImageFormat::Blue)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::RG)
			{
				return m_Bytes[i * 2 + 1];
			}
			else if (m_Format == ImageFormat::RGB)
			{
				return m_Bytes[i * 3 + 1];
			}
			else if (m_Format == ImageFormat::BGR)
			{
				return m_Bytes[i * 3 + 1];
			}
			else if (m_Format == ImageFormat::BGRA)
			{
				return m_Bytes[i * 4 + 1];
			}
			else //if (m_Format == ImageFormat::RGBA)
			{
				return m_Bytes[i * 4 + 1];
			}
		}

		BYTE Bitmap::getBlue(int i)
		{
			if (m_Format == ImageFormat::Red)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Green)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Blue)
			{
				return m_Bytes[i];
			}
			else if (m_Format == ImageFormat::RG)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::RGB)
			{
				return m_Bytes[i * 3 + 2];
			}
			else if (m_Format == ImageFormat::BGR)
			{
				return m_Bytes[i * 3 + 0];
			}
			else if (m_Format == ImageFormat::BGRA)
			{
				return m_Bytes[i * 4 + 0];
			}
			else //if (m_Format == ImageFormat::RGBA)
			{
				return m_Bytes[i * 4 + 2];
			}
		}

		BYTE Bitmap::getAlpha(int i)
		{
			if (m_Format == ImageFormat::Red)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Green)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::Blue)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::RG)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::RGB)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::BGR)
			{
				return 0;
			}
			else if (m_Format == ImageFormat::BGRA)
			{
				return m_Bytes[i * 4 + 3];
			}
			else //if (m_Format == ImageFormat::RGBA)
			{
				return m_Bytes[i * 4 + 3];
			}
		}

		BYTE Bitmap::getPixelStride()
		{
			if (m_Format == ImageFormat::Red || m_Format == ImageFormat::Green || m_Format == ImageFormat::Blue) return 1;
			else if (m_Format == ImageFormat::RG) return 2;
			else if (m_Format == ImageFormat::RGB || m_Format == ImageFormat::BGR) return 3;
			else return 4;
		}
	}
}