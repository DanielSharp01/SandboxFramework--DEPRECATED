#include "Matrix.h"
#include "Vector4.h"

namespace SandboxFramework
{
	namespace Math
	{
		Vector4::Vector4(float x, float y, float z, float w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		Vector4& Vector4::Add(const Vector4& b)
		{
			X += b.X;
			Y += b.Y;
			Z += b.Z;
			W += b.W;
			return *this;
		}

		Vector4& Vector4::Subtract(const Vector4& b)
		{
			X -= b.X;
			Y -= b.Y;
			Z -= b.Z;
			W -= b.W;
			return *this;
		}

		Vector4& Vector4::Multiply(float b)
		{
			X *= b;
			Y *= b;
			Z *= b;
			W *= b;
			return *this;
		}

		Vector4& Vector4::Multiply(const Vector4& b)
		{
			X *= b.X;
			Y *= b.Y;
			Z *= b.Z;
			W *= b.W;
			return *this;
		}

		Vector4& Vector4::Divide(float b)
		{
			X /= b;
			Y /= b;
			Z /= b;
			W /= b;
			return *this;
		}

		Vector4& Vector4::Divide(const Vector4& b)
		{
			X /= b.X;
			Y /= b.Y;
			Z /= b.Z;
			W /= b.W;
			return *this;
		}

		//3D dot product
		float Vector4::Dot(const Vector4& b)
		{
			return (X * b.X) + (Y * b.Y) + (Z * b.Z);
		}

		//3D cross product
		Vector4& Vector4::Cross(const Vector4& b)
		{
			float x = (Y * b.Z) - (Z * b.Y);
			float y = (Z * b.X) - (X * b.Z);
			float z = (X * b.Y) - (Y * b.X);

			X = x;
			Y = y;
			Z = z;
			return *this;
		}

		//3D cross product
		Vector4& Vector4::Cross(Vector4 a, const Vector4& b)
		{
			return a.Cross(b);
		}

		Vector4& Vector4::Transform(const Matrix& b)
		{
			float x = X * b.Elements[0 + 0 * 4] + Y * b.Elements[0 + 1 * 4] + Z * b.Elements[0 + 2 * 4] + W * b.Elements[0 + 3 * 4];
			float y = X * b.Elements[1 + 0 * 4] + Y * b.Elements[1 + 1 * 4] + Z * b.Elements[1 + 2 * 4] + W * b.Elements[1 + 3 * 4];
			float z = X * b.Elements[2 + 0 * 4] + Y * b.Elements[2 + 1 * 4] + Z * b.Elements[2 + 2 * 4] + W * b.Elements[2 + 3 * 4];
			float w = X * b.Elements[3 + 0 * 4] + Y * b.Elements[3 + 1 * 4] + Z * b.Elements[3 + 2 * 4] + W * b.Elements[3 + 3 * 4];

			X = x;
			Y = y;
			Z = z;
			W = w;
			return *this;
		}

		Vector4& Vector4::Transform(Vector4 a, const Matrix& b)
		{
			return a.Transform(b);
		}

		bool Vector4::Equals(const Vector4& b) const
		{
			return X == b.X && Y == b.Y && Z == b.Z && W == b.W;
		}

		Vector4& Vector4::operator+=(const Vector4& b)
		{
			return Add(b);
		}

		Vector4& Vector4::operator-=(const Vector4& b)
		{
			return Subtract(b);
		}

		Vector4& Vector4::operator*=(float b)
		{
			return Multiply(b);
		}

		Vector4& Vector4::operator*=(const Vector4& b)
		{
			return Multiply(b);
		}

		Vector4& Vector4::operator/=(float b)
		{
			return Divide(b);
		}

		Vector4& Vector4::operator/=(const Vector4& b)
		{
			return Divide(b);
		}

		bool operator==(Vector4& a, const Vector4& b)
		{
			return a.Equals(b);
		}

		bool operator!=(Vector4& a, const Vector4& b)
		{
			return !(a.Equals(b));
		}

		Vector4& operator+(Vector4 a, const Vector4& b)
		{
			return a.Add(b);
		}

		Vector4& operator-(Vector4 a, const Vector4& b)
		{
			return a.Subtract(b);
		}

		Vector4& operator*(Vector4 a, float b)
		{
			return a.Multiply(b);
		}

		Vector4& operator*(Vector4 a, const Vector4& b)
		{
			return a.Multiply(b);
		}

		Vector4& operator/(Vector4 a, float b)
		{
			return a.Divide(b);
		}

		Vector4& operator/(Vector4 a, const Vector4& b)
		{
			return a.Divide(b);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector4& b)
		{
			stream << "(" << b.X << ";" << b.Y << ";" << b.Z << ";" << b.W << ")";
			return stream;
		}
	}
}