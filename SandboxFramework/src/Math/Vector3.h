#pragma once

#include <iostream>

namespace Sand
{
	namespace Math
	{
		struct Matrix;

		struct Vector3
		{
			float X, Y, Z;

			Vector3() = default;
			Vector3(float x, float y, float z);

			Vector3& Add(const Vector3& b);
			Vector3& Subtract(const Vector3& b);
			Vector3& Multiply(float b);
			Vector3& Multiply(const Vector3& b);
			Vector3& Divide(float b);
			Vector3& Divide(const Vector3& b);
			float Dot(const Vector3& b);

			Vector3& Cross(const Vector3& b);
			static Vector3 Cross(Vector3 a, const Vector3& b);

			Vector3& Transform(const Matrix& b);
			static Vector3 Transform(Vector3 a, const Matrix& b);
			bool Equals(const Vector3& b) const;

			Vector3& operator+=(const Vector3& b);
			Vector3& operator-=(const Vector3& b);
			Vector3& operator*=(float b);
			Vector3& operator*=(const Vector3& b);
			Vector3& operator/=(float b);
			Vector3& operator/=(const Vector3& b);

			friend bool operator==(Vector3& a, const Vector3& b);
			friend bool operator!=(Vector3& a, const Vector3& b);

			friend Vector3 operator+(Vector3 a, const Vector3& b);
			friend Vector3 operator-(Vector3 a, const Vector3& b);
			friend Vector3 operator*(Vector3 a, float b);
			friend Vector3 operator*(Vector3 a, const Vector3& b);
			friend Vector3 operator/(Vector3 a, float b);
			friend Vector3 operator/(Vector3 a, const Vector3& b);


			friend std::ostream& operator<<(std::ostream& stream, const Vector3& b);
		};
	}
}