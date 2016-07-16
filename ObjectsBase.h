#pragma once
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <SOIL/SOIL.h>

#include "Objects.h"
#include "Shaders.h"


class Object3D
{
protected:
	GLuint* indices;
	float* mapcoords;
	bool VertChange, UseTex;
	string TexFile;

	GLuint VAO, verticesVBO, indicesVBO, textureVBO, tex;
	unsigned int verts, inds, maps;
	int imgWidth, imgHeight;

	GLenum mode;
	GLuint p, f, v;

public:
	/*float3 Velocity;
	float3 Position;
	float3 Rotation;
	float3 Scale;
	float Mass;

	mat4 MVP;*/
};
