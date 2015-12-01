#pragma once

#include "Functions.h"
#include "Vector3.h"
#include "Vector4.h"

namespace SandboxFramework
{
	namespace Math
	{
		struct Matrix
		{
			union
			{
				float Elements[4 * 4];
				Vector4 Columns[4];
			};

			Matrix();
			Matrix(float diagonal);
			Matrix(float elements[4 * 4]);

			Matrix& Multiply(float b);
			Matrix& Multiply(const Matrix& b);

			bool Equals(const Matrix& b) const;

			Matrix& operator*=(float b);
			Matrix& operator*=(const Matrix& b);

			friend Matrix& operator*(Matrix a, float b);
			friend Matrix& operator*(Matrix a, const Matrix& b);

			friend bool operator==(Matrix a, const Matrix& b);
			friend bool operator!=(Matrix a, const Matrix& b);

			friend std::ostream& operator<<(std::ostream& stream, const Matrix& b);

			static bool Inverse(const Matrix& a, Matrix& out);
			static Matrix Identity();

			static Matrix Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix Perspective(float fov, float aspectRatio, float near, float far);

			static Matrix Trasnlation(const Vector3 translation);
			static Matrix Scale(const Vector3 scale);
			static Matrix Rotation(float angle, const Vector3 axis);
		};
	}
}