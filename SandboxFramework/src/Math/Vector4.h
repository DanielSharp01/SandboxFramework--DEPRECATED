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

			Vector4() = default;
			Vector4(float x, float y, float z, float w);

			Vector4& Add(const Vector4& b);
			Vector4& Subtract(const Vector4& b);
			Vector4& Multiply(float b);
			Vector4& Multiply(const Vector4& b);
			Vector4& Divide(float b);
			Vector4& Divide(const Vector4& b);
			float Dot(const Vector4& b);

			Vector4& Cross(const Vector4& b);
			static Vector4 Cross(Vector4 a, const Vector4& b);

			Vector4& Transform(const Matrix& b);
			static Vector4 Transform(Vector4 a, const Matrix& b);
			bool Equals(const Vector4& b) const;

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