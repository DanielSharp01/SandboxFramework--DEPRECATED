#include "Convert.h"

namespace StringUtils
{
	namespace Convert
	{
		bool ToUnsignedInt(std::string str, unsigned int& out)
		{
			out = 0;
			int place = 1;

			for (int i = str.length() - 1; i >= 0; i--)
			{
				int d = str[i] - 48;
				if (d < 0 || d > 9) return false;
				out += d * place;
				place *= 10;
			}

			return true;
		}

		bool ToUnsignedInt(std::string str, int& out)
		{
			out = 0;
			int place = 1;

			for (int i = str.length() - 1; i >= 0; i--)
			{
				int d = str[i] - 48;
				if (d < 0 || d > 9) return false;
				out += d * place;
				place *= 10;
			}

			return true;
		}

		bool ToInt(std::string str, int& out)
		{
			out = 0;
			int place = 1;

			for (int i = str.length() - 1; i >= (str[0] == '-' ? 1 : 0); i--)
			{
				int d = str[i] - 48;
				if (d < 0 || d > 9) return false;
				out += d * place;
				place *= 10;
			}

			if (str[0] == '-') out = -out;
			return true;
		}
	}
}