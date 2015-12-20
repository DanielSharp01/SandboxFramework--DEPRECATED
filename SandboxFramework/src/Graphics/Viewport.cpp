#include "Viewport.h"

namespace Sand
{
	namespace Graphics
	{
			Viewport::Viewport(int width, int height, float near, float far) : m_Width(width), m_Height(height), m_Near(near), m_Far(far)
			{}

			Math::Rectangle Viewport::GetProjected() const
			{
				if (m_Projected.GetArea() > 0) return m_Projected;
				else return Math::Rectangle(0, 0, m_Width, m_Height);
			}

			Math::Matrix Viewport::GetOrthoProjectionMatrix() const
			{
				return Math::Matrix::Orthographic(GetProjected().TopLeft.X, GetProjected().TopRight.X, GetProjected().BottomLeft.Y, GetProjected().TopLeft.Y, m_Near, m_Far);
			}

			void Viewport::SetProjected(float left, float right, float top, float bottom)
			{
				m_Projected = Math::Rectangle(left, top, right - left, bottom - top);
			}

			void Viewport::SetClipping(float near, float far)
			{
				m_Near = near;
				m_Far = far;
			}
	}
}