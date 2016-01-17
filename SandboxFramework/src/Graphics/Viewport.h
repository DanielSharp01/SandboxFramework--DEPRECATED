#pragma once

#include "../Math/Rectangle.h"

namespace Sand
{
	namespace Graphics
	{
		class GraphicsDevice;

		class Viewport
		{
			friend GraphicsDevice;
		private:
#ifdef VISUAL_SCHOOL
			Viewport() {}
#else
			Viewport() = default;
#endif

			Viewport(unsigned short width, unsigned short height, float near, float far);
			unsigned short m_Width;
			unsigned short m_Height;
			float m_Near;
			float m_Far;
		public:
			inline unsigned short GetWidth() const { return m_Width; }
			inline unsigned short GetHeight() const { return m_Height; }
			Math::Matrix GetOrthoProjectionMatrix() const;

			void SetClipping(float near, float far);
		};
	}
}