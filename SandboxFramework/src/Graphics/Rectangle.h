#pragma once

#include "../Math/Vector2.h"
#include "../Math/Matrix.h"

namespace Sand
{
	//TODO: It is not really graphics, think about namespace for the no namespace
	//TODO: Implement this more like vector same conventions, operators
	namespace Graphics
	{
		struct Rectangle
		{
			Math::Vector2 TopLeft;
			Math::Vector2 TopRight;
			Math::Vector2 BottomLeft;
			Math::Vector2 BottomRight;

			Rectangle(float x, float y, float width, float height);

			void Transform(Math::Matrix matrix);
			void Rotate(float angle);

			inline Math::Vector2 GetPosition() { return TopLeft; }
			Math::Vector2 GetCenter();
			Math::Vector2 GetWidth();
			Math::Vector2 GetHeight();
			//TODO: Change to the dist version
			inline float GetArea() { return GetWidth().X * GetHeight().Y; }

			bool Intersects() {} //TODO: Implement Later
			bool Contains() {}
		};
	}
}