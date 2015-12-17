#include "Functions.h"

namespace Sand
{
	namespace Math
	{
		int Random(int min, int max)
		{
			return min + rand() % (max - min + 1);
		}

		float RandomFloat()
		{
			return (float)rand() / (float)RAND_MAX;
		}

		float LinearInterpolation(float min, float max, float rate)
		{
			return min + max * rate;
		}

		float RandomLinearInterpolation(float min, float max)
		{
			return LinearInterpolation(min, max, RandomFloat());
		} 

		float Degree2Radian(float degree)
		{
			return degree * (float)M_PI / (float)180;
		}

		float Radian2Degree(float radian)
		{
			return radian * (float)180 / (float)M_PI;
		}
	}
}