#pragma once

namespace SandboxFramework
{
	namespace Math
	{
		class Vector4;
	}
	namespace Graphics
	{
		struct Color
		{
			float R, G, B, A;

			Color() = default;
			Color(float r, float g, float b, float a);

			Math::Vector4 ToVector4();
			bool Equals(const Color& b) const;

			friend bool operator==(Color a, const Color& b);
			friend bool operator!=(Color a, const Color& b);
		};
	}
}