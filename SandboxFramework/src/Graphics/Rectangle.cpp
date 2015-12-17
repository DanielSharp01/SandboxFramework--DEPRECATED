#include "Rectangle.h"

namespace Sand
{
	namespace Graphics
	{
		Rectangle::Rectangle(float x, float y, float width, float height)
		{
			TopLeft = Math::Vector2(x, y);
			TopRight = Math::Vector2(x + width, y);
			BottomLeft = Math::Vector2(x, y + height);
			BottomRight = Math::Vector2(x + width, y + height);
		}

		void Rectangle::Transform(Math::Matrix matrix)
		{
			TopLeft.Transform(matrix);
			TopRight.Transform(matrix);
			BottomLeft.Transform(matrix);
			BottomRight.Transform(matrix);
		}

		void Rectangle::Rotate(float angle)
		{
			Math::Vector2 center = GetCenter();
			Math::Matrix mat = Math::Matrix::Translation(Math::Vector3(-center.X, -center.Y, 0))
				* Math::Matrix::Rotation(angle, Math::Vector3(0, 0, 1))
				* Math::Matrix::Translation(Math::Vector3(center.X, center.Y, 0));
			TopLeft.Transform(mat);
			TopRight.Transform(mat);
			BottomLeft.Transform(mat);
			BottomRight.Transform(mat);
		}

		Math::Vector2 Rectangle::GetCenter()
		{
			return TopLeft + GetWidth() / 2 + GetHeight() / 2;
		}

		//TODO: Vector distance implementation
		Math::Vector2 Rectangle::GetWidth()
		{
			return TopRight - TopLeft;
		}

		Math::Vector2 Rectangle::GetHeight()
		{
			return BottomLeft - TopLeft;
		}
	}
}