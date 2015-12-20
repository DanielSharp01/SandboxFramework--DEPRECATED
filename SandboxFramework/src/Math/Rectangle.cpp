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
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();

			return contains(b, w, h, calculateInverse(w, h));
		}

		bool Rectangle::Contains(const Rectangle& b) const
		{
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();
			Matrix inverse = calculateInverse(w, h);
			
			return contains(b, w, h, inverse);
		}

		bool Rectangle::contains(const Vector2& b, const Math::Vector2& width, const Math::Vector2& height, const Math::Matrix& inverse) const
		{
			Vector2 point = Vector2::Transform(b, inverse);
			return (point.X >= 0 && point.X <= 1) && (point.Y >= 0 && point.Y <= 1);
		}

		bool Rectangle::contains(const Rectangle& b, const Math::Vector2& width, const Math::Vector2& height, const Math::Matrix& inverse) const
		{
			return contains(b.TopLeft, width, height, inverse) && contains(b.TopRight, width, height, inverse) && contains(b.BottomLeft, width, height, inverse) && contains(b.BottomRight, width, height, inverse);
		}

		Matrix Rectangle::calculateInverse(const Math::Vector2& width, const Math::Vector2& height) const
		{
			Matrix matrix;
			matrix.Columns[0] = Vector4(width.X, width.Y, 0, 0);
			matrix.Columns[1] = Vector4(height.X, height.Y, 0, 0);
			matrix.Columns[2] = Vector4(0, 0, 1, 0);
			matrix.Columns[3] = Vector4(TopLeft.X, TopLeft.Y, 0, 1);
			matrix.Inverse();

			return matrix;
		}

		bool Rectangle::Intersects(const Rectangle& b, bool canContain, bool canBeContained) const
		{
			Vector2 w = GetWidth();
			Vector2 h = GetHeight();
			Matrix inverse = calculateInverse(w, h);
			Vector2 bw = b.GetWidth();
			Vector2 bh = b.GetHeight();
			Matrix binverse = b.calculateInverse(bw, bh);

			if (canBeContained && contains(b, w, h, inverse)) return true;
			if (canContain && b.contains(*this, bw, bh, binverse)) return true;
			
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