#pragma once

#include <GL/glew.h>

struct VBOLocation
{
	int Location;
	int Stride;
	int Offset;

#ifdef VISUAL_SCHOOL
	VBOLocation() {}
#else
	VBOLocation() = default;
#endif

	VBOLocation(int location, int stride = 0, int offset = 0)
		: Location(location), Stride(stride), Offset(offset)
	{ }
};