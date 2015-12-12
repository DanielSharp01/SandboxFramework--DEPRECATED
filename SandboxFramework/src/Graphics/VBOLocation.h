#pragma once

#include <GL/glew.h>

struct VBOLocation
{
	GLint Location;
	GLsizei Stride;
	GLsizei Offset;

	VBOLocation() = default;

	VBOLocation(GLint location, GLsizei stride = 0, GLsizei offset = 0)
		: Location(location), Stride(stride), Offset(offset)
	{ }
};