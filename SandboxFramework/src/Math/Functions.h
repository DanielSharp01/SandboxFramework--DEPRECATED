#pragma once
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

namespace Sand
{
	namespace Math
	{
		int Random(int min, int max);
		float RandomFloat();

		float LinearInterpolation(float min, float max, float rate);
		float RandomLinearInterpolation(float min, float max);

		float Degree2Radian(float degree);
		float Radian2Degree(float radian);
	}
}