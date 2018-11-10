#version 420
in vec3 position;

layout(location=0) in vec4 inPosition;
layout(location=1) in vec2 inTexCoord;
out vec2 exTexCoord;

uniform mat4 viewMatrix;

float pi = 3.14159265358f;

void main(void)
{
	gl_Position = inPosition;

	vec4 tmp = viewMatrix * inPosition;
	exTexCoord = vec2(tmp.x, tmp.y);
}