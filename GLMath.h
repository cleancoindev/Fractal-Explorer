#pragma once
#include "Quaternion.h"
#include "float3.h"
#include "mat4.h"

namespace GLMath
{
	// Float-precision Arithmetic
	float3 Cross(const float3& a, const float3& b);
	float Dot(const float3& a, const float3& b);
	mat4 Rotate(const Quaternion& q);
  	mat4 Translate(const float3& n);
	mat4 Scale(const float3& s);
  	mat4 Scale(float x, float y, float z);
  	mat4 Perspective(float fov, float ratio, float nearZ, float farZ);
  	mat4 Identity();
	mat4 Inverse(const mat4& M);
}
