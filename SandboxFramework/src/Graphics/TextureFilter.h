#pragma once

#include <GL/glew.h>

namespace Sand
{
	namespace Graphics
	{
		enum TextureFilter
		{
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,
			NearestMipNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipLinear = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipLinear = GL_LINEAR_MIPMAP_LINEAR
		};
	}
}