#pragma once

#include <string>
#include "ImageFormat.h"

typedef unsigned char BYTE;

namespace Sand
{
	namespace Graphics
	{
		class Bitmap
		{
		private:
			BYTE* m_Bytes;
			unsigned short m_Width;
			unsigned short m_Height;
			ImageFormat m_Format;
		public:
			Bitmap(BYTE* bytes, unsigned short width, unsigned short height, ImageFormat format = ImageFormat::RGBA);
			~Bitmap();

			static Bitmap* Load(std::string path, bool premultiplied = false);
			void SaveAsPNG(std::string path);
			void SaveAsJPG(std::string path);

			void Premultiply();
			inline BYTE* GetBytes() { return m_Bytes; }
			BYTE* GetCopyOfBytes(ImageFormat format = ImageFormat::RGBA);

			inline unsigned short GetWidth() { return m_Width; }
			inline unsigned short GetHeight() { return m_Height; }
			inline ImageFormat GetFormat() { return m_Format; }
		protected:
			BYTE getRed(int i);
			BYTE getGreen(int i);
			BYTE getBlue(int i);
			BYTE getAlpha(int i);
			BYTE getPixelStride();
		};
	}
}