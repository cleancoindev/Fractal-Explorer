#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

namespace Shaders
{
	void SetShaders(GLuint* p, GLuint* v, GLuint* f, const char* vertShaderFile, const char* FragShaderFile);
}
