#include "Vector2.h"
#include "Matrix.h"

namespace Sand
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

		float Vector2::Dot(const Vector2& b) const
		{
			return (X * b.X) + (Y * b.Y);
		}

		float Vector2::PerpDot(const Vector2& b) const
		{
			return (X * b.Y) - (Y * b.X);
		}

		float Vector2::LengthSquared() const
		{
			return X * X + Y * Y;
		}

		float Vector2::Length() const
		{
			return sqrt(LengthSquared());
		}

		float Vector2::Distance(const Vector2& b) const
		{
			return Vector2(X - b.X, Y - b.Y).Length();
		}

		float Vector2::Angle(const Vector2& b) const
		{
			return asin(Dot(b) / (Length() + b.Length()));
		}

		float Vector2::Distance(Vector2 a, const Vector2& b)
		{
			return Vector2(a.X - b.X, a.Y - b.Y).Length();
		}

		float Vector2::Angle(Vector2 a, const Vector2& b)
		{
			return asin(a.Dot(b) / (a.Length() + b.Length()));
		}

		Vector2& Vector2::Normalize()
		{
			float l = Length();
			X /= l;
			Y /= l;

			return *this;
		}

		Vector2 Vector2::Normalize(Vector2 a)
		{
			return a.Normalize();
		}

		bool Vector2::Equals(const Vector2& b) const
		{
			return X == b.X && Y == b.Y;
		}

		bool Vector2::IntersectAsSegment(const Vector2& startA, const Vector2& a, const Vector2& startB, const Vector2& b)
		{
			float axb = a.PerpDot(b);
			float sbsaxa = (startB - startA).PerpDot(a);

			if (axb == 0 && sbsaxa == 0)
			{
				if (a.Dot(b) < 0) return (startA.LengthSquared() <= startB.LengthSquared()) && ((startB + b).LengthSquared() <= (startA + a).LengthSquared());
				else return (startA.LengthSquared() <= (startB + b).LengthSquared()) && (startB.LengthSquared() <= (startA + a).LengthSquared());
			}
			else if (axb == 0) return false;
			else
			{
				float t = (startB - startA).PerpDot(b) / axb;
				float u = sbsaxa / axb;

				return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
			}
		}

		Vector2 Vector2::operator-() const
		{
			return Vector2(-X, -Y);
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