#include "OpenGL.h"
#include "Shaders.h"

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <string.h>

//const char* IMAGE_FILE = "balls.png";
//const char* IMAGE_FILE = "awesome.bmp";
//const char* IMAGE_FILE = "koala.png";
//const char* IMAGE_FILE = "now-its-personal.png";
//const char* IMAGE_FILE = "yellow_pattern.png";
//const char* IMAGE_FILE = "fire.png";
const char* IMAGE_FILE = "full_saturation_spectrum.png";
//const char* IMAGE_FILE = "spectrum.png";
//const char* IMAGE_FILE = "deep_sea.png";
//const char* IMAGE_FILE = "clowning-around.png";

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

int OpenGL::GLInit(int argc, char** argv, int width, int height, const std::string& title)
{
	const char* imageFile;
	if(argc == 1) {
		imageFile = IMAGE_FILE;
	} else if(argc == 2) {
		imageFile = argv[1];
	} else {
		std::cerr << "Unknown arguments received\n";
		return -1;
	}

	filling = true;
	fullscreen = false;
	Position = double3(0);
	Velocity = double3(0);
	framesPerSecond = 60.0;						// not the worst guess
	deltaTime = 0.0;

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
		return -2;
	}

	// GLEW
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW\n";
		return -3;
	}

	GLfloat vertices[] = {
		-1.0, 1.0, 0.0, 1.0,
		1.0, 1.0, 0.0, 1.0,
		1.0, -1.0, 0.0, 1.0,
		-1.0, -1.0, 0.0, 1.0
	};

	GLfloat texCoords[] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};

	GLubyte indices[] = {
		0, 1, 2, 0, 2, 3
	};

	// Shaders
	Shaders::SetShaders(&programId, &vertexShaderId, &fragmentShaderId, "vert_double.glsl", "frag_double.glsl");

	// VBO (Creating objects)
	glGenVertexArrays(1, &vaoId);													// One vaoID per Object
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);														// One buffer per Object
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);							//layout location 0 set to vert4 vertices
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Texture
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	int imgWidth, imgHeight;
	unsigned char* image = SOIL_load_image(imageFile, &imgWidth, &imgHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glGenBuffers(1, &texBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, texBufferId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);							//layout location 1 set to vert2 texture coordinates
	glEnableVertexAttribArray(1);

	// GL
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glViewport(0, 0, width, height);

	return 0;
}

void OpenGL::Draw()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
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

    // Render to Framebuffer 4X current screen size
    const int magnifyFactor = 4;
	const int width = Width() * magnifyFactor;
	const int height = Height() * magnifyFactor;
	GLuint fboId, renderBuffer;
	glGenFramebuffers(1, &fboId);
	glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, width, height);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboId);

	glViewport(0, 0, width, height);
	this->Draw();

	unsigned char* img = new unsigned char[width * height * 3];
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fboId);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
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

    // Delete image array data
	delete[] img;
	delete[] swapSpace;

	// Delete FBO data
	glDeleteFramebuffers(1, &fboId);
	glDeleteRenderbuffers(1, &renderBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width/magnifyFactor, height/magnifyFactor);
}

double OpenGL::FramesPerSecond() const
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

double OpenGL::DeltaTime() const
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
