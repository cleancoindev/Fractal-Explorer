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
	float framesPerSecond;
	unsigned int currentTime, previousTime, elapsedTime;
	float deltaTime;
	bool filling, fullscreen;

public:
	float3 Position;
	float3 Rotation;
	float3 Velocity;

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

	float FramesPerSecond() const;
	GLuint WindowId() const;
	GLuint ProgramId() const;
	float DeltaTime() const;
	int Width() const;
  	int Height() const;
};
