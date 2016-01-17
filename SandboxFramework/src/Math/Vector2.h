#pragma once

#include <iostream>

namespace Sand
{
	namespace Math
	{
		struct Matrix;

		struct Vector2
		{
			float X, Y;

#ifdef VISUAL_SCHOOL
			Vector2() : X(0), Y(0) {}
#else
			Vector2() = default;
#endif
			Vector2(float x, float y);

			Vector2& Add(const Vector2& b);
			Vector2& Subtract(const Vector2& b);
			Vector2& Multiply(float b);
			Vector2& Multiply(const Vector2& b);
			Vector2& Divide(float b);
			Vector2& Divide(const Vector2& b);
			float Dot(const Vector2& b) const;
			float PerpDot(const Vector2& b) const;

			float LengthSquared() const;
			float Length() const;
			float Distance(const Vector2& b) const;
			float Angle(const Vector2& b) const;

			static float Distance(Vector2 a, const Vector2& b);
			static float Angle(Vector2 a, const Vector2& b);

			Vector2& Transform(const Matrix& b);
			static Vector2 Transform(Vector2 a, const Matrix& b);
			Vector2& Normalize();
			static Vector2 Normalize(Vector2 a);
			bool Equals(const Vector2& b) const;

			static bool IntersectAsSegment(const Vector2& startA, const Vector2& a, const Vector2& startB, const Vector2& b);

			Vector2 operator-() const;
			Vector2& operator+=(const Vector2& b);
			Vector2& operator-=(const Vector2& b);
			Vector2& operator*=(float b);
			Vector2& operator*=(const Vector2& b);
			Vector2& operator/=(float b);
			Vector2& operator/=(const Vector2& b);

			friend bool operator==(Vector2& a, const Vector2& b);
			friend bool operator!=(Vector2& a, const Vector2& b);

			friend Vector2 operator+(Vector2 a, const Vector2& b);
			friend Vector2 operator-(Vector2 a, const Vector2& b);
			friend Vector2 operator*(Vector2 a, float b);
			friend Vector2 operator*(Vector2 a, const Vector2& b);
			friend Vector2 operator/(Vector2 a, float b);
			friend Vector2 operator/(Vector2 a, const Vector2& b);


			friend std::ostream& operator<<(std::ostream& stream, const Vector2& b);
		};
	}
}