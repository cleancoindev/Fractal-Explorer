#pragma once
#include "Quaternion.h"

class dmat4
{
public:
	double p[4][4];

	dmat4();
	dmat4(double num);
	dmat4(double* m);
	dmat4(const dmat4& A);

	dmat4 operator* (const dmat4& B) const;
	Quaternion operator* (const Quaternion& q) const;

	dmat4& operator= (const dmat4& Src);
	bool operator== (const dmat4& Src) const;
};
