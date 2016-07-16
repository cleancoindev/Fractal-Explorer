#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>
#include <string>

#include "GLMath.h"
//#include "Objects.h"


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
	//std::vector<std::shared_ptr<Object3D>> objects;

public:
	float3 Position;
	float3 Rotation;
	float3 Velocity;

	OpenGL();
	OpenGL(int argc, char** argv, int width, int height, const std::string& title);
  	~OpenGL();

	void GLInit(int argc, char** argv, int width, int height, const std::string& title);
  	void Cleanup();
	void CalcFPS();
  	void StartFPS();
	void Fullscreen();
  	void Wireframe();
	void SaveScreenshot(const std::string& filename);

	/*std::shared_ptr<Object3D> AddObject(int Verts, int Inds, int Mode);
	std::shared_ptr<Object3D> AddCube();
	std::shared_ptr<Object3D> AddSphere(unsigned int n, float radius);
	std::shared_ptr<Object3D> AddLine();
	std::shared_ptr<Object3D> AddPlane();*/

	float FramesPerSecond() const;
	GLuint WindowId() const;
	GLuint ProgramId() const;
	float DeltaTime() const;
	int Width() const;
  	int Height() const;
};
