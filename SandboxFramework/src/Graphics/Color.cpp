#include "Color.h"

namespace Sand
{
	namespace Graphics
	{
		Color::Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {};

		bool Color::Equals(const Color& b) const
		{
			return R == b.R && G == b.G && B == b.B && A == b.A;
		}

		Math::Vector4 Color::ToVector4()
		{
			return Math::Vector4(R, G, B, A);
		}

		bool operator==(Color a, const Color& b)
		{
			return a.Equals(b);
		}

		bool operator!=(Color a, const Color& b)
		{
			return !(a.Equals(b));
		}
	}
}