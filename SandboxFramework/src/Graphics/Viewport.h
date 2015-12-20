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
			Viewport() = default;
			Viewport(int width, int height, float near, float far);
			unsigned int m_Width;
			unsigned int m_Height;
			Math::Rectangle m_Projected;
			float m_Near;
			float m_Far;
		public:
			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }
			inline float GetProjectedWidth() const { return GetProjected().GetWidth().X; }
			inline float GetProjectedHeight() const { return GetProjected().GetHeight().Y; }
			Math::Rectangle GetProjected() const;
			Math::Matrix GetOrthoProjectionMatrix() const;

			void SetProjected(float left, float right, float top, float bottom);
			void SetClipping(float near, float far);
		};
	}
}