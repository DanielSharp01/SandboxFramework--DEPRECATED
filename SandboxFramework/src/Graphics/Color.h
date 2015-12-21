#pragma once

#include "../Math/Vector4.h"

namespace Sand
{
	namespace Graphics
	{
		struct Color
		{
			float R, G, B, A;

			Color() = default;
			Color(float r, float g, float b, float a);

			Math::Vector4 ToVector4();
			
			Color& Multiply(float b);
			Color& Multiply(const Color& b);

			bool Equals(const Color& b) const;

			Color& operator*=(float b);
			Color& operator*=(const Color& b);

			friend Color operator*(Color a, float b);
			friend Color operator*(Color a, const Color& b);

			friend bool operator==(Color a, const Color& b);
			friend bool operator!=(Color a, const Color& b);
		};
	}
}