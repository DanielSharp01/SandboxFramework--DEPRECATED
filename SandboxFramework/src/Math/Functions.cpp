#include "Functions.h"

namespace SandboxFramework
{
	namespace Math
	{
		int random(int min, int max)
		{
			return min + rand() % (max - min + 1);
		}

		float randomFloat()
		{
			return (float)rand() / (float)RAND_MAX;
		}

		float linearInterpolation(float min, float max, float rate)
		{
			return min + max * rate;
		}

		float randomLinearInterpolation(float min, float max)
		{
			return linearInterpolation(min, max, randomFloat());
		} 

		float degree2Radian(float degree)
		{
			return degree * (float)M_PI / (float)180;
		}

		float radian2Degree(float radian)
		{
			return radian * (float)180 / (float)M_PI;
		}
	}
}