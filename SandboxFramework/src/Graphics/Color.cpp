#include "Color.h"

namespace Sand
{
	namespace Graphics
	{
		Color::Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {};

		Color& Color::Multiply(float b)
		{
			R *= b;
			G *= b;
			B *= b;
			A *= b;
			return *this;
		}

		Color& Color::Multiply(const Color& b)
		{
			R *= b.R;
			G *= b.G;
			B *= b.B;
			A *= b.A;
			return *this;
		}

		bool Color::Equals(const Color& b) const
		{
			return R == b.R && G == b.G && B == b.B && A == b.A;
		}

		Math::Vector4 Color::ToVector4()
		{
			return Math::Vector4(R, G, B, A);
		}

		Color& Color::operator*=(float b)
		{
			return Multiply(b);
		}

		Color& Color::operator*=(const Color& b)
		{
			return Multiply(b);
		}

		Color operator*(Color a, float b)
		{
			return a.Multiply(b);
		}

		Color operator*(Color a, const Color& b)
		{
			return a.Multiply(b);
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