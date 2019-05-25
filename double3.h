#pragma once

class double3
{
public:
	double x, y, z;
	double3(double x, double y, double z);
	double3(double k);
	double3();

	void CompWiseDiv(const double3& Src);
	void CompWiseMult(const double3& Src);

 	double Magnitude() const;
  	void Normalize();

	double3& operator= (const double3& Src);
	bool operator== (const double3& cmp) const;
	double3& operator+= (const double3 Src);
	double3& operator-= (const double3 Src);

	double3 operator+ (double3 Src) const;
	double3 operator- (double3 Src) const;
	double3 operator- () const;
	double3 operator/ (double Num) const;
	double3 operator* (double Num) const;
};
