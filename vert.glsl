#version 400
in vec3 position;

layout(location=0) in vec4 inPosition;
layout(location=1) in vec4 inColour;
layout(location=2) in vec2 inTexCoord;
out vec4 exColour;
out vec2 exTexCoord;

uniform mat4 viewMatrix;

float pi = 3.14159265358f;

void main(void)
{
	gl_Position = inPosition;
	exColour = inColour;

	// Texture with inverted inputs
	//exTexCoord = inTexCoord;

        vec4 tmp = viewMatrix * inPosition;
	exTexCoord = vec2(tmp.x, tmp.y);
}
