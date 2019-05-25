#version 420
in vec3 position;

layout(location=0) in vec4 inPosition;
layout(location=1) in vec2 inTexCoord;
out vec4 unmodifiedPos;

void main(void)
{
	gl_Position = inPosition;
	unmodifiedPos = inPosition;
}