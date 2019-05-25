#pragma once
#include "Quaternion.h"
#include "float3.h"
#include "mat4.h"
#include "double3.h"
#include "dmat4.h"

namespace GLMath
{
	// Float-precision Arithmetic
	float3 Cross(const float3& a, const float3& b);
	float Dot(const float3& a, const float3& b);
	mat4 Rotate(const Quaternion& q);
  	mat4 Translate(const float3& n);
	mat4 Scale(const float3& s);
  	mat4 Scale(float x, float y, float z);
  	mat4 Identity();
	mat4 Inverse(const mat4& M);
}

namespace GLMathDouble
{
	// Double-precision Arithmetic
	double3 Cross(const double3& a, const double3& b);
	double Dot(const double3& a, const double3& b);
  	dmat4 Translate(const double3& n);
	dmat4 Scale(const double3& s);
  	dmat4 Scale(double x, double y, double z);
  	dmat4 Identity();
	dmat4 Inverse(const dmat4& M);
}
