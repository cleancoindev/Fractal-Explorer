#pragma once
#include "float3.h"

class Quaternion
{
public:
	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(float k);
	Quaternion(float3 num, float w);
	Quaternion(const Quaternion& q);

  	float Magnitude() const;
	void Normalize();
	Quaternion Conjugate() const;
	float3 ToFloat3() const;
	Quaternion operator* (const Quaternion& Src) const;
	Quaternion& operator+= (const float3& Src);
	Quaternion& operator-= (const float3& Src);
	Quaternion& operator= (const Quaternion& Src);
};
