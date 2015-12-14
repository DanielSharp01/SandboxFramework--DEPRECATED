#include "Vector2.h"
#include "Matrix.h"

namespace SandboxFramework
{
	namespace Math
	{
		Vector2::Vector2(float x, float y)
		{
			X = x;
			Y = y;
		}

		Vector2& Vector2::Add(const Vector2& b)
		{
			X += b.X;
			Y += b.Y;
			return *this;
		}

		Vector2& Vector2::Subtract(const Vector2& b)
		{
			X -= b.X;
			Y -= b.Y;
			return *this;
		}

		Vector2& Vector2::Multiply(float b)
		{
			X *= b;
			Y *= b;
			return *this;
		}

		Vector2& Vector2::Multiply(const Vector2& b)
		{
			X *= b.X;
			Y *= b.Y;
			return *this;
		}

		Vector2& Vector2::Transform(const Matrix& b)
		{
			float x = X * b.Elements[0 + 0 * 4] + Y * b.Elements[0 + 1 * 4] + 0 * b.Elements[0 + 2 * 4] + 1 * b.Elements[0 + 3 * 4];
			float y = X * b.Elements[1 + 0 * 4] + Y * b.Elements[1 + 1 * 4] + 0 * b.Elements[0 + 2 * 4] + 1 * b.Elements[1 + 3 * 4];
			
			X = x;
			Y = y;
			return *this;
		}

		Vector2 Vector2::Transform(Vector2 a, const Matrix& b)
		{
			return a.Transform(b);
		}

		Vector2& Vector2::Divide(float b)
		{
			X /= b;
			Y /= b;
			return *this;
		}

		Vector2& Vector2::Divide(const Vector2& b)
		{
			X /= b.X;
			Y /= b.Y;
			return *this;
		}

		float Vector2::Dot(const Vector2& b)
		{
			return (X * b.X) + (Y * b.Y);
		}

		float Vector2::PerpDot(const Vector2& b)
		{
			return (X * b.Y) - (Y * b.X);
		}

		bool Vector2::Equals(const Vector2& b) const
		{
			return X == b.X && Y == b.Y;
		}

		Vector2& Vector2::operator+=(const Vector2& b)
		{
			return Add(b);
		}

		Vector2& Vector2::operator-=(const Vector2& b)
		{
			return Subtract(b);
		}

		Vector2& Vector2::operator*=(float b)
		{
			return Multiply(b);
		}

		Vector2& Vector2::operator*=(const Vector2& b)
		{
			return Multiply(b);
		}

		Vector2& Vector2::operator/=(float b)
		{
			return Divide(b);
		}

		Vector2& Vector2::operator/=(const Vector2& b)
		{
			return Divide(b);
		}

		bool operator==(Vector2& a, const Vector2& b)
		{
			return a.Equals(b);
		}

		bool operator!=(Vector2& a, const Vector2& b)
		{
			return !(a.Equals(b));
		}

		Vector2 operator+(Vector2 a, const Vector2& b)
		{
			return a.Add(b);
		}

		Vector2 operator-(Vector2 a, const Vector2& b)
		{
			return a.Subtract(b);
		}

		Vector2 operator*(Vector2 a, float b)
		{
			return a.Multiply(b);
		}

		Vector2 operator*(Vector2 a, const Vector2& b)
		{
			return a.Multiply(b);
		}

		Vector2 operator/(Vector2 a, float b)
		{
			return a.Divide(b);
		}

		Vector2 operator/(Vector2 a, const Vector2& b)
		{
			return a.Divide(b);
		}

		std::ostream& operator<<(std::ostream& stream, const Vector2& b)
		{
			stream << "(" << b.X << ";" << b.Y << ")";
			return stream;
		}

	}
}