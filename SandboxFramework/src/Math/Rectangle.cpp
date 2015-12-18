#include "Rectangle.h"

namespace Sand
{
	namespace Math
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

		//TODO: Look into getting angle just for fun
		void Rectangle::Rotate(float angle)
		{
			Math::Vector2 center = GetCenter();
			Math::Matrix mat = Math::Matrix::Translation(Math::Vector3(center.X, center.Y, 0))
				* Math::Matrix::Rotation(angle, Math::Vector3(0, 0, 1))
				* Math::Matrix::Translation(Math::Vector3(-center.X, -center.Y, 0));

			TopLeft.Transform(mat);
			TopRight.Transform(mat);
			BottomLeft.Transform(mat);
			BottomRight.Transform(mat);
		}

		Math::Vector2 Rectangle::GetCenter() const
		{
			return TopLeft + GetWidth() / 2 + GetHeight() / 2;
		}

		Math::Vector2 Rectangle::GetWidth() const
		{
			return TopRight - TopLeft;
		}

		Math::Vector2 Rectangle::GetHeight() const
		{
			return BottomLeft - TopLeft;
		}

		void Rectangle::SetPosition(Math::Vector2 position)
		{
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();
			TopLeft = Math::Vector2(position.X, position.Y);
			TopRight = Math::Vector2(TopLeft.X + w.X, TopLeft.Y + w.Y);
			BottomLeft = Math::Vector2(TopLeft.X + h.X, TopLeft.Y + h.Y);
			BottomRight = Math::Vector2(TopLeft.X + w.X + h.X, TopLeft.Y + w.Y + h.Y);
		}

		void Rectangle::SetCenter(Math::Vector2 center)
		{
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();
			TopLeft = Math::Vector2(center.X - w.X / 2 - h.X / 2, center.Y - w.Y / 2 - h.Y / 2);
			TopRight = Math::Vector2(TopLeft.X + w.X, TopLeft.Y + w.Y);
			BottomLeft = Math::Vector2(TopLeft.X + h.X, TopLeft.Y + h.Y);
			BottomRight = Math::Vector2(TopLeft.X + w.X + h.X, TopLeft.Y + w.Y + h.Y);
		}

		void Rectangle::SetWidth(float width)
		{
			Vector2 w = GetHeight().Normalize() * width;
			Vector2 h = GetHeight();
			TopRight = Math::Vector2(TopLeft.X + w.X, TopLeft.Y + w.Y);
			BottomRight = Math::Vector2(TopLeft.X + w.X + h.X, TopLeft.Y + w.Y + h.Y);
		}

		void Rectangle::SetHeight(float height)
		{
			Vector2 w = GetHeight();
			Vector2 h = GetHeight().Normalize() * height;
			BottomLeft = Math::Vector2(TopLeft.X + h.X, TopLeft.Y + h.Y);
			BottomRight = Math::Vector2(TopLeft.X + w.X + h.X, TopLeft.Y + w.Y + h.Y);
		}

		bool Rectangle::Contains(const Vector2& b) const
		{
			Vector2 p = TopLeft;
			//TODO: Maybe abstract out (performance)
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();

			Matrix matrix;
			matrix.Columns[0] = Vector4(w.X, w.Y, 0, 0);
			matrix.Columns[1] = Vector4(h.X, h.Y, 0, 0);
			matrix.Columns[2] = Vector4(0, 0, 1, 0);
			matrix.Columns[3] = Vector4(p.X, p.Y, 0, 1);
			matrix.Inverse();

			Vector2 point = Vector2::Transform(b, matrix);

			return (point.X >= 0 && point.X <= 1) && (point.Y >= 0 && point.Y <= 1);
		}

		bool Rectangle::Contains(const Rectangle& b) const
		{
			return Contains(b.TopLeft) && Contains(b.TopRight) && Contains(b.BottomLeft) && Contains(b.BottomRight);
		}

		//Line segment intersection
		bool Rectangle::Intersects(const Rectangle& b) const
		{
			if (Contains(b)) return true;

			Vector2 w = GetWidth();
			Vector2 h = GetHeight();
			Vector2 bw = b.GetWidth();
			Vector2 bh = b.GetHeight();

			if (Vector2::IntersectAsSegment(TopLeft, w, b.TopLeft, bw)
				|| Vector2::IntersectAsSegment(TopLeft, w, b.TopRight, bh)
				|| Vector2::IntersectAsSegment(TopLeft, w, b.TopLeft, bh)
				|| Vector2::IntersectAsSegment(TopLeft, w, b.BottomLeft, bw)

				|| Vector2::IntersectAsSegment(TopRight, h, b.TopLeft, bw)
				|| Vector2::IntersectAsSegment(TopRight, h, b.TopRight, bh)
				|| Vector2::IntersectAsSegment(TopRight, h, b.TopLeft, bh)
				|| Vector2::IntersectAsSegment(TopRight, h, b.BottomLeft, bw)

				|| Vector2::IntersectAsSegment(TopLeft, h, b.TopLeft, bw)
				|| Vector2::IntersectAsSegment(TopLeft, h, b.TopRight, bh)
				|| Vector2::IntersectAsSegment(TopLeft, h, b.TopLeft, bh)
				|| Vector2::IntersectAsSegment(TopLeft, h, b.BottomLeft, bw)

				|| Vector2::IntersectAsSegment(BottomLeft, w, b.TopLeft, bw)
				|| Vector2::IntersectAsSegment(BottomLeft, w, b.TopRight, bh)
				|| Vector2::IntersectAsSegment(BottomLeft, w, b.TopLeft, bh)
				|| Vector2::IntersectAsSegment(BottomLeft, w, b.BottomLeft, bw)) return true;
			else return false;
		}
	}
}