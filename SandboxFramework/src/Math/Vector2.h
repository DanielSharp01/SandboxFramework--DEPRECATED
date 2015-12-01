#pragma once

#include <iostream>

namespace SandboxFramework
{
	namespace Math
	{
		struct Matrix;

		struct Vector2
		{
			float X, Y;

			Vector2() = default;
			Vector2(float x, float y);

			Vector2& Add(const Vector2& b);
			Vector2& Subtract(const Vector2& b);
			Vector2& Multiply(float b);
			Vector2& Multiply(const Vector2& b);
			Vector2& Divide(float b);
			Vector2& Divide(const Vector2& b);
			float Dot(const Vector2& b);
			float PerpDot(const Vector2& b);

			Vector2& Transform(const Matrix& b);
			static Vector2& Transform(Vector2 a, const Matrix& b);
			bool Equals(const Vector2& b) const;

			Vector2& operator+=(const Vector2& b);
			Vector2& operator-=(const Vector2& b);
			Vector2& operator*=(float b);
			Vector2& operator*=(const Vector2& b);
			Vector2& operator/=(float b);
			Vector2& operator/=(const Vector2& b);

			friend bool operator==(Vector2& a, const Vector2& b);
			friend bool operator!=(Vector2& a, const Vector2& b);

			friend Vector2& operator+(Vector2 a, const Vector2& b);
			friend Vector2& operator-(Vector2 a, const Vector2& b);
			friend Vector2& operator*(Vector2 a, float b);
			friend Vector2& operator*(Vector2 a, const Vector2& b);
			friend Vector2& operator/(Vector2 a, float b);
			friend Vector2& operator/(Vector2 a, const Vector2& b);


			friend std::ostream& operator<<(std::ostream& stream, const Vector2& b);
		};
	}
}