#include "dmat4.h"
#include <cmath>

dmat4::dmat4()
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			p[col][row] = 0.0;
}

dmat4::dmat4(double num)
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			p[col][row] = num;
}

dmat4::dmat4(double* m)
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			p[col][row] = m[(4*col) + row];
}

dmat4::dmat4(const dmat4& A)
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			p[col][row] = A.p[col][row];
}

dmat4 dmat4::operator* (const dmat4& B) const
{
	dmat4 C;
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			C.p[col][row] = ((p[0][row] * B.p[col][0]) + (p[1][row] * B.p[col][1]) + (p[2][row] * B.p[col][2]) + (p[3][row] * B.p[col][3]));

	return C;
}

Quaternion dmat4::operator* (const Quaternion& q) const
{
	Quaternion r(0.0f);
	r.x = ((p[0][0] * q.x) + (p[0][1] * q.y) + (p[0][2] * q.z) + (p[0][3] * q.w));
	r.y = ((p[1][0] * q.x) + (p[1][1] * q.y) + (p[1][2] * q.z) + (p[1][3] * q.w));
	r.z = ((p[2][0] * q.x) + (p[2][1] * q.y) + (p[2][2] * q.z) + (p[2][3] * q.w));
	r.w = ((p[3][0] * q.x) + (p[3][1] * q.y) + (p[3][2] * q.z) + (p[3][3] * q.w));
	return r;
}

dmat4& dmat4::operator= (const dmat4& Src)
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			p[col][row] = Src.p[col][row];

	return *this;
}

bool dmat4::operator== (const dmat4& Src) const
{
	for(int col = 0; col < 4; col++)
		for(int row = 0; row < 4; row++)
			if(p[col][row] != Src.p[col][row])
				return false;

	return true;
}
