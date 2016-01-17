#pragma once

#include <iostream>

namespace Sand
{
	namespace Math
	{
		struct Matrix;

		struct Vector4
		{
			float X, Y, Z, W;

#ifdef VISUAL_SCHOOL
			Vector4() : X(0), Y(0), Z(0), W(1) {}
#else
			Vector4() = default;
#endif
			Vector4(float x, float y, float z, float w);

			Vector4& Add(const Vector4& b);
			Vector4& Subtract(const Vector4& b);
			Vector4& Multiply(float b);
			Vector4& Multiply(const Vector4& b);
			Vector4& Divide(float b);
			Vector4& Divide(const Vector4& b);
			float Dot(const Vector4& b) const;

			Vector4& Cross(const Vector4& b);
			static Vector4 Cross(Vector4 a, const Vector4& b);

			float LengthSquared() const;
			float Length() const;
			float Distance(const Vector4& b) const;
			float Angle(const Vector4& b) const;

			static float Distance(Vector4 a, const Vector4& b);
			static float Angle(Vector4 a, const Vector4& b);

			Vector4& Transform(const Matrix& b);
			static Vector4 Transform(Vector4 a, const Matrix& b);
			Vector4& Normalize();
			static Vector4 Normalize(Vector4 a);
			bool Equals(const Vector4& b) const;

			Vector4 operator-() const;
			Vector4& operator+=(const Vector4& b);
			Vector4& operator-=(const Vector4& b);
			Vector4& operator*=(float b);
			Vector4& operator*=(const Vector4& b);
			Vector4& operator/=(float b);
			Vector4& operator/=(const Vector4& b);

			friend bool operator==(Vector4& a, const Vector4& b);
			friend bool operator!=(Vector4& a, const Vector4& b);

			friend Vector4 operator+(Vector4 a, const Vector4& b);
			friend Vector4 operator-(Vector4 a, const Vector4& b);
			friend Vector4 operator*(Vector4 a, float b);
			friend Vector4 operator*(Vector4 a, const Vector4& b);
			friend Vector4 operator/(Vector4 a, float b);
			friend Vector4 operator/(Vector4 a, const Vector4& b);


			friend std::ostream& operator<<(std::ostream& stream, const Vector4& b);
		};
	}
}