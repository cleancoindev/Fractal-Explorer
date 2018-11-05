#include "OpenGL.h"
#include "Shaders.h"

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <string.h>

//const char* IMAGE_FILE = "balls.png";
//const char* IMAGE_FILE = "awesome.bmp";
//const char* IMAGE_FILE = "image.png";
//const char* IMAGE_FILE = "now-its-personal.png";
const char* IMAGE_FILE = "yellow_pattern.png";
//const char* IMAGE_FILE = "fire.png";
//const char* IMAGE_FILE = "full_saturation_spectrum.png";
//const char* IMAGE_FILE = "spectrum.png";
//const char* IMAGE_FILE = "deep_sea.png";

OpenGL::OpenGL()
{
	return;
}

OpenGL::OpenGL(int argc, char** argv, int width, int height, const std::string& title)
{
	GLInit(argc, argv, width, height, title);
}

OpenGL::~OpenGL()
{
	// Shader Cleanup
	glUseProgram(0);

	glDetachShader(programId, vertexShaderId);
	glDetachShader(programId, fragmentShaderId);

	glDeleteShader(fragmentShaderId);
	glDeleteShader(vertexShaderId);

	glDeleteProgram(programId);

	// VBO Cleanup
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &colourBufferId);
	glDeleteBuffers(1, &vboId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
}

void OpenGL::GLInit(int argc, char** argv, int width, int height, const std::string& title)
{
	filling = true;
	fullscreen = false;
	//Position = float3(1.570796327, 0, 0);
	Position = float3(0, 0, 0);
	Rotation = 0.0f;
	Velocity = 0.0f;
	framesPerSecond = 60.0f;						// not the worst guess
	deltaTime = 0.0f;

	// FREEGLUT
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	if((windowId = glutCreateWindow(title.c_str())) < 1)
	{
		std::cerr << "Failed to create GLUT window\n";
		return;
	}

	// GLEW
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		return;
	}

	GLfloat vertices[] = {
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f
	};

	GLfloat colours[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};

	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
	};

	GLubyte indices[] = {
		0, 1, 2, 0, 2, 3
	};

	// Shaders
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, "vert.glsl", "frag.glsl");

	// VBO (Creating objects)
	glGenVertexArrays(1, &vaoId);													// One vaoID per Object
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);														// One buffer per Object
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);							//layout location 0 set to vert4 vertices
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colourBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, colourBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);							//layout location 1 set to vert4 colours
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Texture
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	int imgWidth, imgHeight;
	unsigned char* image = SOIL_load_image(IMAGE_FILE, &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glGenBuffers(1, &texBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, texBufferId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);							//layout location 2 set to vert2 texture coordinates
	glEnableVertexAttribArray(2);

	// GL
	glClearColor(0.0, 0.0, 0.0, 1.0);
	int fbWidth, fbHeight;
	glViewport(0, 0, fbWidth, fbHeight);
}

void OpenGL::CalcFPS()
{
	frameCount++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	if(currentTime - previousTime > 200)
	{
		framesPerSecond = frameCount * 1000.0f / (currentTime - previousTime);
		deltaTime = 1.0f / framesPerSecond;
		previousTime = currentTime;
		frameCount = 0;
	}
}

void OpenGL::StartFPS()
{
	previousTime = glutGet(GLUT_ELAPSED_TIME);
}

void OpenGL::Fullscreen()
{
	fullscreen ? glutReshapeWindow(800, 600) : glutFullScreen();
	fullscreen = !fullscreen;
}

void OpenGL::Wireframe()
{
	filling = !filling;
	filling ?
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) :
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL::SaveScreenshot(const std::string& filename)
{
	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	const int width = Width();
	const int height = Height();
	unsigned char* img = new unsigned char[width * height * 3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	unsigned char* swapSpace = new unsigned char[width * height * 3];
	const int bytesPerRow = width * 3;
	for(unsigned int i = 0; i < height; i++)
	{
		memcpy(&swapSpace[i * bytesPerRow], &img[(height - i - 1) * bytesPerRow], bytesPerRow);
	}

	if(!SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, width, height, 3, swapSpace))
	{
		std::cerr << "SaveScreenshot failed\n";
	}
	else
	{
		std::cerr << "SaveScreenshot succeeded\n";
	}
	delete[] img;
	delete[] swapSpace;
}

/*Object3D* OpenGL::AddObject(int Verts, int Inds, int Mode)
{
	Objects.push_back(new Object3D(Verts, Inds, Mode));
	return Objects[Objects.size() - 1];
}

Object3D* OpenGL::AddCube()
{
	Objects.push_back(new CubeObj());
	return Objects[Objects.size() - 1];
}

Object3D* OpenGL::AddSphere(unsigned int n, float radius)
{
	Objects.push_back(new SphereObj(n, radius));
	return Objects[Objects.size() - 1];
}

Object3D* OpenGL::AddLine()
{
	Objects.push_back(new LineObj());
	return Objects[Objects.size() - 1];
}

Object3D* OpenGL::AddPlane()
{
	Objects.push_back(new PlaneObj());
	return Objects[Objects.size() - 1];
}*/

float OpenGL::FramesPerSecond() const
{
	return framesPerSecond;
}

GLuint OpenGL::ProgramId() const
{
	return programId;
}

GLuint OpenGL::WindowId() const
{
	return windowId;
}

float OpenGL::DeltaTime() const
{
	return deltaTime;
}

int OpenGL::Width() const
{
	return glutGet(GLUT_WINDOW_WIDTH);
}

int OpenGL::Height() const
{
	return glutGet(GLUT_WINDOW_HEIGHT);
}
