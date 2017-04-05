#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(float k)
{
	x = k;
	y = k;
	z = k;
	w = k;
}

Quaternion::Quaternion(float3 num, float w)
{
	x = num.x;
	y = num.y;
	z = num.z;
	this->w = w;
}

Quaternion::Quaternion(const Quaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

float Quaternion::Magnitude() const
{
  	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

void Quaternion::Normalize()
{
	float magnitude = Magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	w /= magnitude;
}

Quaternion Quaternion::Conjugate() const
{
	return Quaternion(-x, -y, -z, w);
}

float3 Quaternion::ToFloat3() const
{
	return float3(x, y, z);
}

Quaternion Quaternion::operator* (const Quaternion& Src) const
{
	return Quaternion  ((w*Src.x) + (x*Src.w) + (y*Src.z) - (z*Src.y),\
						(w*Src.y) - (x*Src.z) + (y*Src.w) + (z*Src.x),\
						(w*Src.z) + (x*Src.y) - (y*Src.x) + (z*Src.w),\
						(w*Src.w) - (x*Src.x) - (y*Src.y) - (z*Src.z));
}

Quaternion& Quaternion::operator+= (const float3& Src)
{
	x += Src.x;
	y += Src.y;
	z += Src.z;
	return *this;
}

Quaternion& Quaternion::operator-= (const float3& Src)
{
	x -= Src.x;
	y -= Src.y;
	z -= Src.z;
	return *this;
}

Quaternion& Quaternion::operator= (const Quaternion& Src)
{
	x = Src.x;
	y = Src.y;
	z = Src.z;
	w = Src.w;
	return *this;
}
