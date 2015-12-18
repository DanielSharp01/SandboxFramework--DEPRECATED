#include "Matrix.h"

#include "Functions.h"

namespace Sand
{
	namespace Math
	{
		Matrix::Matrix()
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				Elements[i] = 0;
			}
		}

		Matrix::Matrix(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				Elements[i] = 0;
			}

			Elements[0 + 0 * 4] = diagonal;
			Elements[1 + 1 * 4] = diagonal;
			Elements[2 + 2 * 4] = diagonal;
			Elements[3 + 3 * 4] = diagonal;
		}

		Matrix::Matrix(float elements[4 * 4])
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				Elements[i] = elements[i];
			}
		}

		Matrix& Matrix::Multiply(float b)
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				Elements[i] *= b;
			}

			return *this;
		}


		Matrix& Matrix::Multiply(const Matrix& b)
		{
			float newElements[4 * 4];
			for (int c = 0; c < 4; c++)
			{
				for (int r = 0; r < 4; r++)
				{
					float sum = 0;
					for (int e = 0; e < 4; e++)
					{
						sum += Elements[r + e * 4] * b.Elements[e + c * 4];
					}
					newElements[r + c * 4] = sum;
				}
			}

			for (int i = 0; i < 4 * 4; i++)
			{
				Elements[i] = newElements[i];
			}

			return *this;
		}

		Matrix& Matrix::Inverse()
		{
			float inv[16], det;
			int i;

			inv[0] = Elements[5] * Elements[10] * Elements[15] -
				Elements[5] * Elements[11] * Elements[14] -
				Elements[9] * Elements[6] * Elements[15] +
				Elements[9] * Elements[7] * Elements[14] +
				Elements[13] * Elements[6] * Elements[11] -
				Elements[13] * Elements[7] * Elements[10];

			inv[4] = -Elements[4] * Elements[10] * Elements[15] +
				Elements[4] * Elements[11] * Elements[14] +
				Elements[8] * Elements[6] * Elements[15] -
				Elements[8] * Elements[7] * Elements[14] -
				Elements[12] * Elements[6] * Elements[11] +
				Elements[12] * Elements[7] * Elements[10];

			inv[8] = Elements[4] * Elements[9] * Elements[15] -
				Elements[4] * Elements[11] * Elements[13] -
				Elements[8] * Elements[5] * Elements[15] +
				Elements[8] * Elements[7] * Elements[13] +
				Elements[12] * Elements[5] * Elements[11] -
				Elements[12] * Elements[7] * Elements[9];

			inv[12] = -Elements[4] * Elements[9] * Elements[14] +
				Elements[4] * Elements[10] * Elements[13] +
				Elements[8] * Elements[5] * Elements[14] -
				Elements[8] * Elements[6] * Elements[13] -
				Elements[12] * Elements[5] * Elements[10] +
				Elements[12] * Elements[6] * Elements[9];

			inv[1] = -Elements[1] * Elements[10] * Elements[15] +
				Elements[1] * Elements[11] * Elements[14] +
				Elements[9] * Elements[2] * Elements[15] -
				Elements[9] * Elements[3] * Elements[14] -
				Elements[13] * Elements[2] * Elements[11] +
				Elements[13] * Elements[3] * Elements[10];

			inv[5] = Elements[0] * Elements[10] * Elements[15] -
				Elements[0] * Elements[11] * Elements[14] -
				Elements[8] * Elements[2] * Elements[15] +
				Elements[8] * Elements[3] * Elements[14] +
				Elements[12] * Elements[2] * Elements[11] -
				Elements[12] * Elements[3] * Elements[10];

			inv[9] = -Elements[0] * Elements[9] * Elements[15] +
				Elements[0] * Elements[11] * Elements[13] +
				Elements[8] * Elements[1] * Elements[15] -
				Elements[8] * Elements[3] * Elements[13] -
				Elements[12] * Elements[1] * Elements[11] +
				Elements[12] * Elements[3] * Elements[9];

			inv[13] = Elements[0] * Elements[9] * Elements[14] -
				Elements[0] * Elements[10] * Elements[13] -
				Elements[8] * Elements[1] * Elements[14] +
				Elements[8] * Elements[2] * Elements[13] +
				Elements[12] * Elements[1] * Elements[10] -
				Elements[12] * Elements[2] * Elements[9];

			inv[2] = Elements[1] * Elements[6] * Elements[15] -
				Elements[1] * Elements[7] * Elements[14] -
				Elements[5] * Elements[2] * Elements[15] +
				Elements[5] * Elements[3] * Elements[14] +
				Elements[13] * Elements[2] * Elements[7] -
				Elements[13] * Elements[3] * Elements[6];

			inv[6] = -Elements[0] * Elements[6] * Elements[15] +
				Elements[0] * Elements[7] * Elements[14] +
				Elements[4] * Elements[2] * Elements[15] -
				Elements[4] * Elements[3] * Elements[14] -
				Elements[12] * Elements[2] * Elements[7] +
				Elements[12] * Elements[3] * Elements[6];

			inv[10] = Elements[0] * Elements[5] * Elements[15] -
				Elements[0] * Elements[7] * Elements[13] -
				Elements[4] * Elements[1] * Elements[15] +
				Elements[4] * Elements[3] * Elements[13] +
				Elements[12] * Elements[1] * Elements[7] -
				Elements[12] * Elements[3] * Elements[5];

			inv[14] = -Elements[0] * Elements[5] * Elements[14] +
				Elements[0] * Elements[6] * Elements[13] +
				Elements[4] * Elements[1] * Elements[14] -
				Elements[4] * Elements[2] * Elements[13] -
				Elements[12] * Elements[1] * Elements[6] +
				Elements[12] * Elements[2] * Elements[5];

			inv[3] = -Elements[1] * Elements[6] * Elements[11] +
				Elements[1] * Elements[7] * Elements[10] +
				Elements[5] * Elements[2] * Elements[11] -
				Elements[5] * Elements[3] * Elements[10] -
				Elements[9] * Elements[2] * Elements[7] +
				Elements[9] * Elements[3] * Elements[6];

			inv[7] = Elements[0] * Elements[6] * Elements[11] -
				Elements[0] * Elements[7] * Elements[10] -
				Elements[4] * Elements[2] * Elements[11] +
				Elements[4] * Elements[3] * Elements[10] +
				Elements[8] * Elements[2] * Elements[7] -
				Elements[8] * Elements[3] * Elements[6];

			inv[11] = -Elements[0] * Elements[5] * Elements[11] +
				Elements[0] * Elements[7] * Elements[9] +
				Elements[4] * Elements[1] * Elements[11] -
				Elements[4] * Elements[3] * Elements[9] -
				Elements[8] * Elements[1] * Elements[7] +
				Elements[8] * Elements[3] * Elements[5];

			inv[15] = Elements[0] * Elements[5] * Elements[10] -
				Elements[0] * Elements[6] * Elements[9] -
				Elements[4] * Elements[1] * Elements[10] +
				Elements[4] * Elements[2] * Elements[9] +
				Elements[8] * Elements[1] * Elements[6] -
				Elements[8] * Elements[2] * Elements[5];

			det = Elements[0] * inv[0] + Elements[1] * inv[4] + Elements[2] * inv[8] + Elements[3] * inv[12];

			if (det == 0) return *this;

			det = 1.0 / det;

			float invOut[16];
			for (i = 0; i < 16; i++)
				Elements[i] = inv[i] * det;

			return *this;
		}

		bool Matrix::Equals(const Matrix& b) const
		{
			for (int i = 0; i < 4 * 4; i++)
			{
				if (Elements[i] != b.Elements[i]) return false;
			}

			return true;
		}

		Matrix& Matrix::operator*=(float b)
		{
			return Multiply(b);
		}

		Matrix& Matrix::operator*=(const Matrix& b)
		{
			return Multiply(b);
		}

		Matrix operator*(Matrix a, float b)
		{
			return a.Multiply(b);
		}

		Matrix operator*(Matrix a, const Matrix& b)
		{
			return a.Multiply(b);
		}

		bool operator==(Matrix a, const Matrix& b)
		{
			return a.Equals(b);
		}

		bool operator!=(Matrix a, const Matrix& b)
		{
			return !(a.Equals(b));
		}

		std::ostream& operator<<(std::ostream& stream, const Matrix& b)
		{
			stream << "[ " << b.Elements[0 + 0 * 4] << " " << b.Elements[0 + 1 * 4] << " " << b.Elements[0 + 2 * 4] << " " << b.Elements[0 + 3 * 4] << " ]" << std::endl;
			stream << "[ " << b.Elements[1 + 0 * 4] << " " << b.Elements[1 + 1 * 4] << " " << b.Elements[1 + 2 * 4] << " " << b.Elements[1 + 3 * 4] << " ]" << std::endl;
			stream << "[ " << b.Elements[2 + 0 * 4] << " " << b.Elements[2 + 1 * 4] << " " << b.Elements[2 + 2 * 4] << " " << b.Elements[2 + 3 * 4] << " ]" << std::endl;
			stream << "[ " << b.Elements[3 + 0 * 4] << " " << b.Elements[3 + 1 * 4] << " " << b.Elements[3 + 2 * 4] << " " << b.Elements[3 + 3 * 4] << " ]";

			return stream;
		}

		Matrix Matrix::Inverse(Matrix a)
		{
			return a.Inverse();
		}

		Matrix Matrix::Identity()
		{
			return Matrix(1);
		}

		Matrix Matrix::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix result;
			result.Elements[0 + 0 * 4] = 2 / (right - left);
			result.Elements[1 + 1 * 4] = 2 / (top - bottom);
			result.Elements[2 + 2 * 4] = -2 / (far - near);
			result.Elements[0 + 3 * 4] = -(right + left) / (right - left);
			result.Elements[1 + 3 * 4] = -(top + bottom) / (top - bottom);
			result.Elements[2 + 3 * 4] = -(far + near) / (far - near);
			result.Elements[3 + 3 * 4] = 1;

			return result;
		}

		Matrix Matrix::Perspective(float fov, float aspectRatio, float near, float far)
		{
			Matrix result;

			float q = 1.0 / tan(Degree2Radian(0.5f * fov));

			result.Elements[0 + 0 * 4] = q;
			result.Elements[1 + 1 * 4] = q / aspectRatio;
			result.Elements[2 + 2 * 4] = -(far + near) / (far - near);
			result.Elements[2 + 3 * 4] = - 2 * (near * far) / (far - near);
			result.Elements[3 + 2 * 4] = -1;

			return result;
		}

		Matrix Matrix::Translation(const Vector3 translation)
		{
			Matrix result(1.0f);

			result.Elements[0 + 3 * 4] = translation.X;
			result.Elements[1 + 3 * 4] = translation.Y;
			result.Elements[2 + 3 * 4] = translation.Z;

			return result;
		}

		Matrix Matrix::Scale(const Vector3 scale)
		{
			Matrix result(1.0f);

			result.Elements[0 + 0 * 4] = scale.X;
			result.Elements[1 + 1 * 4] = scale.Y;
			result.Elements[2 + 2 * 4] = scale.Z;

			return result;
		}
		Matrix Matrix::Rotation(float angle, const Vector3 axis)
		{
			Matrix result(1.0f);

			float r = Degree2Radian(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.X;
			float y = axis.Y;
			float z = axis.Z;

			result.Elements[0 + 0 * 4] = x * omc + c;
			result.Elements[1 + 0 * 4] = y * x * omc + z * s;
			result.Elements[2 + 0 * 4] = x * z * omc - y * s;

			result.Elements[0 + 1 * 4] = x * y * omc - z * s;
			result.Elements[1 + 1 * 4] = y * omc + c;
			result.Elements[2 + 1 * 4] = y * z * omc + x * s;

			result.Elements[0 + 2 * 4] = x * z * omc + y * s;
			result.Elements[1 + 2 * 4] = y * z * omc - x * s;
			result.Elements[2 + 2 * 4] = z * omc + c;

			return result;
		}
	}
}