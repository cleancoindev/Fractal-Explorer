#include <cmath>
#include "float3.h"

float3::float3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float3::float3(float k)
{
	x = k;
	y = k;
	z = k;
}

float3::float3()
{
	x = 0;
	y = 0;
	z = 0;
}

void float3::CompWiseDiv(const float3& Src)
{
	x /= Src.x;
  	y /= Src.y;
  	z /= Src.z;
}

void float3::CompWiseMult(const float3& Src)
{
	x *= Src.x;
  	y *= Src.y;
  	z *= Src.z;
}

float float3::Magnitude() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

void float3::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

float3& float3::operator= (const float3& Src)
{
	x = Src.x;
	y = Src.y;
	z = Src.z;
	return *this;
}

bool float3::operator== (const float3& cmp) const
{
	if(x == cmp.x && y == cmp.y && z == cmp.z)
		return true;
	else
		return false;
}
float3& float3::operator+= (const float3 Src)
{
	x += Src.x;
	y += Src.y;
	z += Src.z;
	return *this;
}

float3& float3::operator-= (const float3 Src)
{
	x -= Src.x;
	y -= Src.y;
	z -= Src.z;
	return *this;
}

float3 float3::operator+ (float3 Src) const
{
	return float3(x + Src.x, y + Src.y, z + Src.z);
}

float3 float3::operator- (float3 Src) const
{
	return float3(x - Src.x, y - Src.y, z - Src.z);
}

float3 float3::operator- () const
{
	return float3(-x, -y, -z);
}

float3 float3::operator/ (float Num) const
{
	return float3(x / Num, y / Num, z / Num);
}

float3 float3::operator* (float Num) const
{
	return float3(x * Num, y * Num, z * Num);
}
