#pragma once

namespace SandboxFramework
{
	namespace Graphics
	{
		struct Color
		{
			float R, G, B, A;

			Color() = default;
			Color(float r, float g, float b, float a);

			bool Equals(const Color& b) const;
			friend bool operator==(Color a, const Color& b);
			friend bool operator!=(Color a, const Color& b);
		};
	}
}