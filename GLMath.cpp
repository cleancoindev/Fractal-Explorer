#include "GLMath.h"
#include <cmath>

float3 GLMath::Cross(const float3& a, const float3& b)
{
	return float3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

float GLMath::Dot(const float3& a, const float3& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

mat4 GLMath::Rotate(const Quaternion& q)
{
	float c = cosf(q.w);
	float s = sinf(q.w);

	mat4 r;
	r.p[0][0] = c + ((q.x * q.x) * (1 - c));
	r.p[0][1] = (q.y * q.x) * (1 - c) + (q.z * s);
	r.p[0][2] = (q.z * q.x) * (1 - c) - (q.y * s);
	r.p[0][3] = 0.0f;

	r.p[1][0] = (q.x * q.y) * (1 - c) - (q.z * s);
	r.p[1][1] = c + ((q.y * q.y) * (1 - c));
	r.p[1][2] = (q.z * q.y) * (1 - c) + (q.x * s);
	r.p[1][3] = 0.0f;

	r.p[2][0] = (q.x * q.z) * (1 - c) + (q.y * s);
	r.p[2][1] = (q.y * q.z) * (1 - c) - (q.x * s);
	r.p[2][2] = c + ((q.z * q.z) * (1 - c));
	r.p[2][3] = 0.0f;

	r.p[3][0] = 0.0f;
	r.p[3][1] = 0.0f;
	r.p[3][2] = 0.0f;
	r.p[3][3] = 1.0f;

	return r;
}

mat4 GLMath::Translate(const float3& n)
{
	mat4 result(0.0);
	result.p[0][0] = 1.0;
	result.p[1][1] = 1.0;
	result.p[2][2] = 1.0;
	result.p[3][3] = 1.0;

	result.p[3][0] = n.x;
	result.p[3][1] = n.y;
	result.p[3][2] = n.z;

	return result;
}

mat4 GLMath::Scale(const float3& s)
{
	mat4 m(0.0);
	m.p[0][0] = s.x;
	m.p[1][1] = s.y;
	m.p[2][2] = s.z;
	m.p[3][3] = 1;
	return m;
}

mat4 GLMath::Scale(float x, float y, float z)
{
	mat4 m(0.0);
	m.p[0][0] = x;
	m.p[1][1] = y;
	m.p[2][2] = z;
	m.p[3][3] = 1;
	return m;
}

mat4 GLMath::Identity()
{
	mat4 ident(0.0);
	for(int i = 0; i < 4; i++)
	{
		ident.p[i][i] = 1;
	}
	return ident;
}

mat4 GLMath::Inverse(const mat4& M)
{
	float* m;
	m = (float*)(&M.p[0]);
	float inv[16], det;
	float invOut[16];

	inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
	inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
	inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
	inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
	inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
	inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
	inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
	inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
	inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
	inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
	inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
	inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if(det == 0)
	    return Identity();

	det = 1.f / det;

	for(int i = 0; i < 16; i++)
	    invOut[i] = inv[i] * det;

	return mat4(invOut);
}


// Double Arithmetic
// =============================================================================

double3 GLMathDouble::Cross(const double3& a, const double3& b)
{
	return double3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

double GLMathDouble::Dot(const double3& a, const double3& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

dmat4 GLMathDouble::Translate(const double3& n)
{
	dmat4 result(0.0);
	result.p[0][0] = 1.0;
	result.p[1][1] = 1.0;
	result.p[2][2] = 1.0;
	result.p[3][3] = 1.0;

	result.p[3][0] = n.x;
	result.p[3][1] = n.y;
	result.p[3][2] = n.z;

	return result;
}

dmat4 GLMathDouble::Scale(const double3& s)
{
	dmat4 m(0.0);
	m.p[0][0] = s.x;
	m.p[1][1] = s.y;
	m.p[2][2] = s.z;
	m.p[3][3] = 1;
	return m;
}

dmat4 GLMathDouble::Scale(double x, double y, double z)
{
	dmat4 m(0.0);
	m.p[0][0] = x;
	m.p[1][1] = y;
	m.p[2][2] = z;
	m.p[3][3] = 1;
	return m;
}

dmat4 GLMathDouble::Identity()
{
	dmat4 ident(0.0);
	for(int i = 0; i < 4; i++)
	{
		ident.p[i][i] = 1;
	}
	return ident;
}

dmat4 GLMathDouble::Inverse(const dmat4& M)
{
	double* m;
	m = (double*)(&M.p[0]);
	double inv[16], det;
	double invOut[16];

	inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
	inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
	inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
	inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
	inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
	inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
	inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
	inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
	inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
	inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
	inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
	inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if(det == 0)
	    return Identity();

	det = 1.f / det;

	for(int i = 0; i < 16; i++)
	    invOut[i] = inv[i] * det;

	return dmat4(invOut);
}
