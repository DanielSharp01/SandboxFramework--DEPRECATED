#include "Viewport.h"

namespace Sand
{
	namespace Graphics
	{
			Viewport::Viewport(int width, int height, float near, float far) : m_Width(width), m_Height(height), m_Near(near), m_Far(far)
			{}

			Math::Matrix Viewport::GetOrthoProjectionMatrix() const
			{
				return Math::Matrix::Orthographic(0, m_Width, m_Height, 0, m_Near, m_Far);
			}

			void Viewport::SetClipping(float near, float far)
			{
				m_Near = near;
				m_Far = far;
			}
	}
}