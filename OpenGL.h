#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include <string>

#include "GLMath.h"


class OpenGL
{
private:
	GLuint windowId;
	GLuint programId, fragmentShaderId, vertexShaderId, vaoId, vboId, colourBufferId, indexBufferId, textureId, texBufferId;
	unsigned int frameCount;
	double framesPerSecond;
	unsigned int currentTime, previousTime, elapsedTime;
	double deltaTime;
	bool filling, fullscreen;

public:
	double3 Position;
	double3 Velocity;

	OpenGL();
	OpenGL(int argc, char** argv, int width, int height, const std::string& title);
	~OpenGL();

	void GLInit(int argc, char** argv, int width, int height, const std::string& title);
	void Cleanup();
	void Draw();
	void CalcFPS();
	void StartFPS();
	void Fullscreen();
	void Wireframe();
	void SaveScreenshot(const std::string& filename);

	double FramesPerSecond() const;
	GLuint WindowId() const;
	GLuint ProgramId() const;
	double DeltaTime() const;
	int Width() const;
	int Height() const;
};
