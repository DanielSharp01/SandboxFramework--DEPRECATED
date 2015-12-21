#pragma once

namespace Sand
{
	namespace Graphics
	{
		enum GLType
		{
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			HalfFloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,
			Fixed = GL_FIXED,
			Int2101010Rev = GL_INT_2_10_10_10_REV,
			UsignedInt2101010Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
			UnsignedInt10F11F11FRev = GL_UNSIGNED_INT_10F_11F_11F_REV
		};
	}
}