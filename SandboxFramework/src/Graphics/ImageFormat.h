#pragma once

#include <GL/glew.h>

namespace Sand
{
	namespace Graphics
	{
		enum ImageFormat
		{
			Red = GL_RED,
			Green = GL_GREEN,
			Blue = GL_BLUE,
			RG = GL_RG,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA
		};
	}
}