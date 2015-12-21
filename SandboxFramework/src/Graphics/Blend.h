#pragma once

#include <GL/glew.h>

namespace Sand
{
	namespace Graphics
	{
		enum Blend
		{
			Zero = GL_ZERO,
			One = GL_ONE,
			SourceAlpha = GL_SRC_ALPHA,
			InverseSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
			SourceColor = GL_SRC_COLOR,
			InverseSourceColor = GL_ONE_MINUS_SRC_COLOR,
			DestinationAlpha = GL_DST_ALPHA,
			InverseDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
			DestinationColor = GL_DST_COLOR,
			InverseDestinationColor = GL_ONE_MINUS_DST_COLOR,
			BlendFactor = GL_CONSTANT_COLOR,
			InverseBlendFactor = GL_ONE_MINUS_CONSTANT_COLOR,
			BlendFactorAlpha = GL_CONSTANT_ALPHA,
			InverseBlendFactorAlpha = GL_ONE_MINUS_CONSTANT_ALPHA
		};
	}
}