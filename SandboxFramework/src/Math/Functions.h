#pragma once
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

namespace SandboxFramework
{
	namespace Math
	{
		int random(int min, int max);
		float randomFloat();

		float linearInterpolation(float min, float max, float rate);
		float randomLinearInterpolation(float min, float max);

		float degree2Radian(float degree);
		float radian2Degree(float radian);
	}
}