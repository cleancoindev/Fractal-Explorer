#include <cmath>
#include "double3.h"

double3::double3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double3::double3(double k)
{
	x = k;
	y = k;
	z = k;
}

double3::double3()
{
	x = 0;
	y = 0;
	z = 0;
}

void double3::CompWiseDiv(const double3& Src)
{
	x /= Src.x;
  	y /= Src.y;
  	z /= Src.z;
}

void double3::CompWiseMult(const double3& Src)
{
	x *= Src.x;
  	y *= Src.y;
  	z *= Src.z;
}

double double3::Magnitude() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

void double3::Normalize()
{
	double mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

double3& double3::operator= (const double3& Src)
{
	x = Src.x;
	y = Src.y;
	z = Src.z;
	return *this;
}

bool double3::operator== (const double3& cmp) const
{
	if(x == cmp.x && y == cmp.y && z == cmp.z)
		return true;
	else
		return false;
}
double3& double3::operator+= (const double3 Src)
{
	x += Src.x;
	y += Src.y;
	z += Src.z;
	return *this;
}

double3& double3::operator-= (const double3 Src)
{
	x -= Src.x;
	y -= Src.y;
	z -= Src.z;
	return *this;
}

double3 double3::operator+ (double3 Src) const
{
	return double3(x + Src.x, y + Src.y, z + Src.z);
}

double3 double3::operator- (double3 Src) const
{
	return double3(x - Src.x, y - Src.y, z - Src.z);
}

double3 double3::operator- () const
{
	return double3(-x, -y, -z);
}

double3 double3::operator/ (double Num) const
{
	return double3(x / Num, y / Num, z / Num);
}

double3 double3::operator* (double Num) const
{
	return double3(x * Num, y * Num, z * Num);
}
