#pragma once

#include "Vector2.h"
#include "Matrix.h"

namespace Sand
{
	//TODO: Equals operator
	//TODO: Implement this more like vector same conventions, operators
	namespace Math
	{
		struct Rectangle
		{
			Math::Vector2 TopLeft;
			Math::Vector2 TopRight;
			Math::Vector2 BottomLeft;
			Math::Vector2 BottomRight;
			
			Rectangle() = default;
			Rectangle(float x, float y, float width, float height);

			void Transform(Math::Matrix matrix);
			void Rotate(float angle);

			inline Math::Vector2 GetPosition() const { return TopLeft; }
			Math::Vector2 GetCenter() const;
			Math::Vector2 GetWidth() const;
			Math::Vector2 GetHeight() const;

			inline float GetArea() const { return GetWidth().Length() * GetHeight().Length(); }
			
			void SetPosition(Math::Vector2 position);
			void SetCenter(Math::Vector2 center);
			void SetWidth(float width);
			void SetHeight(float height);

			bool Contains(const Vector2& b) const;
			bool Contains(const Rectangle& b) const;

			bool Intersects(const Rectangle& b) const;
		};
	}
}