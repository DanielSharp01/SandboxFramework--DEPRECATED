#include "Matrix.h"
#include "Vector3.h"

namespace Sand
{
	namespace Math
	{
		Vector3::Vector3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Vector3& Vector3::Add(const Vector3& b)
		{
			X += b.X;
			Y += b.Y;
			Z += b.Z;
			return *this;
		}

		Vector3& Vector3::Subtract(const Vector3& b)
		{
			X -= b.X;
			Y -= b.Y;
			Z -= b.Z;
			return *this;
		}

		Vector3& Vector3::Multiply(float b)
		{
			X *= b;
			Y *= b;
			Z *= b;
			return *this;
		}

		Vector3& Vector3::Multiply(const Vector3& b)
		{
			X *= b.X;
			Y *= b.Y;
			Z *= b.Z;
			return *this;
		}

		Vector3& Vector3::Divide(float b)
		{
			X /= b;
			Y /= b;
			Z /= b;
			return *this;
		}

		Vector3& Vector3::Divide(const Vector3& b)
		{
			X /= b.X;
			Y /= b.Y;
			Z /= b.Z;
			return *this;
		}

		float Vector3::Dot(const Vector3& b)
		{
			return (X * b.X) + (Y * b.Y) + (Z * b.Z);
		}

		Vector3& Vector3::Cross(const Vector3& b)
		{
			float x = (Y * b.Z) - (Z * b.Y);
			float y = (Z * b.X) - (X * b.Z);
			float z = (X * b.Y) - (Y * b.X);

			X = x;
			Y = y;
			Z = z;
			return *this;
		}

		Vector3 Vector3::Cross(Vector3 a, const Vector3& b)
		{
			return a.Cross(b);
		}

		Vector3& Vector3::Transform(const Matrix& b)
		{
			float x = X * b.Elements[0 + 0 * 4] + Y * b.Elements[0 + 1 * 4] + Z * b.Elements[0 + 2 * 4] + 1 * b.Elements[0 + 3 * 4];
			float y = X * b.Elements[1 + 0 * 4] + Y * b.Elements[1 + 1 * 4] + Z * b.Elements[1 + 2 * 4] + 1 * b.Elements[1 + 3 * 4];
			float z = X * b.Elements[2 + 0 * 4] + Y * b.Elements[2 + 1 * 4] + Z * b.Elements[2 + 2 * 4] + 1 * b.Elements[2 + 3 * 4];

			X = x;
			Y = y;
			Z = z;
			return *this;
		}

		Vector3 Vector3::Transform(Vector3 a, const Matrix& b)
		{
			return a.Transform(b);
		}

		bool Vector3::Equals(const Vector3& b) const
		{
			return X == b.X && Y == b.Y && Z == b.Z;
		}

		Vector3& Vector3::operator+=(const Vector3& b)
		{
			return Add(b);
		}

		Vector3& Vector3::operator-=(const Vector3& b)
		{
			return Subtract(b);
		}

		Vector3& Vector3::operator*=(float b)
		{
			return Multiply(b);
		}

		Vector3& Vector3::operator*=(const Vector3& b)
		{
			return Multiply(b);
		}

		Vector3& Vector3::operator/=(float b)
		{
			return Divide(b);
		}

		Vector3& Vector3::operator/=(const Vector3& b)
		{
			return Divide(b);
		}

		bool operator==(Vector3& a, const Vector3& b)
		{
			return a.Equals(b);
		}

		bool operator!=(Vector3& a, const Vector3& b)
		{
			return !(a.Equals(b));
		}

		Vector3 operator+(Vector3 a, const Vector3& b)
		{
			return a.Add(b);
		}

		Vector3 operator-(Vector3 a, const Vector3& b)
		{
			return a.Subtract(b);
		}

		Vector3 operator*(Vector3 a, float b)
		{
			return a.Multiply(b);
		}

		Vector3 operator*(Vector3 a, const Vector3& b)
		{
			return a.Multiply(b);
		}

		Vector3 operator/(Vector3 a, float b)
		{
			return a.Divide(b);
		}

		Vector3 operator/(Vector3 a, const Vector3& b)
		{
			return a.Divide(b);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector3& b)
		{
			stream << "(" << b.X << ";" << b.Y << ";" << b.Z << ")";
			return stream;
		}
	}
}