#include "MathUtil.h"
#include "quaternion.h"
#include <cmath>

fMat4 MathUtil::translate(const fVec3& mov)
{
	return translate(mov.x, mov.y, mov.z);
}

fMat4 MathUtil::translate(const float& x, const float& y, const float& z)
{
	return fMat4(1, 0, 0, x,
				 0, 1, 0, y, 
		         0, 0, 1, z, 
		         0, 0, 0, 1);
}

fMat4 MathUtil::scale(const fVec3& sc)
{
	return scale( sc.x, sc.y, sc.z);
}

fMat4 MathUtil::scale(float sc)
{
	return scale(sc, sc, sc);
}

fMat4 MathUtil::scale(const float& x, const float& y, const float& z)
{
	return fMat4(x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

fMat4 MathUtil::rotation(const fVec3& rot)
{
	return rotation(rot.x, rot.y, rot.z);
}

fMat4 MathUtil::rotation(const Quaternion& q)
{
	fMat4 dst;
	float x2 = q.x + q.x;
	float y2 = q.y + q.y;
	float z2 = q.z + q.z;

	float xx2 = q.x * x2;
	float yy2 = q.y * y2;
	float zz2 = q.z * z2;
	float xy2 = q.x * y2;
	float xz2 = q.x * z2;
	float yz2 = q.y * z2;
	float wx2 = q.w * x2;
	float wy2 = q.w * y2;
	float wz2 = q.w * z2;

	dst.m_data[0] = 1.0f - yy2 - zz2;
	dst.m_data[1] = xy2 + wz2;
	dst.m_data[2] = xz2 - wy2;
	dst.m_data[3] = 0.0f;
	   
	dst.m_data[4] = xy2 - wz2;
	dst.m_data[5] = 1.0f - xx2 - zz2;
	dst.m_data[6] = yz2 + wx2;
	dst.m_data[7] = 0.0f;
	   
	dst.m_data[8] = xz2 + wy2;
	dst.m_data[9] = yz2 - wx2;
	dst.m_data[10] = 1.0f - xx2 - yy2;
	dst.m_data[11] = 0.0f;
	   
	dst.m_data[12] = 0.0f;
	dst.m_data[13] = 0.0f;
	dst.m_data[14] = 0.0f;
	dst.m_data[15] = 1.0f;

	return dst;
}

fMat4 MathUtil::rotation(const float& _rotationX, const float& _rotationY, const float& _rotationZ)
{
	fMat4 rot;
	Quaternion _rotationQuat;

	float halfRadx = CC_DEGREES_TO_RADIANS(_rotationX / 2.f), halfRady = CC_DEGREES_TO_RADIANS(_rotationY / 2.f), halfRadz =  -CC_DEGREES_TO_RADIANS(_rotationZ / 2.f);
	float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
	_rotationQuat.x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
	_rotationQuat.y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
	_rotationQuat.z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
	_rotationQuat.w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;

	return rotation(_rotationQuat);
}

float MathUtil::determinant(const fMat4& mat)
{
	const float* m = mat.m_data;

	float a0 = m[0] * m[5] - m[1] * m[4];
	float a1 = m[0] * m[6] - m[2] * m[4];
	float a2 = m[0] * m[7] - m[3] * m[4];
	float a3 = m[1] * m[6] - m[2] * m[5];
	float a4 = m[1] * m[7] - m[3] * m[5];
	float a5 = m[2] * m[7] - m[3] * m[6];
	float b0 = m[8] * m[13] - m[9] * m[12];
	float b1 = m[8] * m[14] - m[10] * m[12];
	float b2 = m[8] * m[15] - m[11] * m[12];
	float b3 = m[9] * m[14] - m[10] * m[13];
	float b4 = m[9] * m[15] - m[11] * m[13];
	float b5 = m[10] * m[15] - m[11] * m[14];

	// Calculate the determinant.
	return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}
bool MathUtil::decompose(const fMat4& mat, fVec3* sc, Quaternion* rot, fVec3* translation)
{
	if (translation) {
		translation->x = mat.m_data[12];
		translation->y = mat.m_data[13];
		translation->z = mat.m_data[14];
	}

	if (sc == nullptr && rot == nullptr) return true;

	fVec3 xaxis(mat.m_data[0], mat.m_data[1], mat.m_data[3]);
	float scaleX = xaxis.getLen();

	fVec3 yaxis(mat.m_data[4], mat.m_data[5], mat.m_data[6]);
	float scaleY = yaxis.getLen();

	fVec3 zaxis(mat.m_data[8], mat.m_data[9], mat.m_data[10]);
	float scaleZ = zaxis.getLen();

	float det = determinant(mat);

	if (det < 0)
		scaleZ = -scaleZ;

	if (sc) {
		sc->x = scaleX;
		sc->y = scaleY;
		sc->z = scaleZ;
	}

	if (rot == nullptr) {
		return true;
	}

	if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || std::abs(scaleZ) < MATH_TOLERANCE)
		return false;

	float rn;

	rn = 1.0f / scaleX;

	xaxis.x *= rn;
	xaxis.y *= rn;
	xaxis.z *= rn;

	rn = 1.0f / scaleY;

	yaxis.x *= rn;
	yaxis.y *= rn;
	yaxis.z *= rn;

	rn = 1.0f / scaleZ;

	zaxis.x *= rn;
	zaxis.y *= rn;
	zaxis.z *= rn;

	float trace = xaxis.x + yaxis.y + zaxis.z + 1.0f;

	if (trace > MATH_EPSILON)
	{
		float s = 0.5f / std::sqrt(trace);
		rot->w = 0.25f / s;
		rot->x = (yaxis.z - zaxis.y) * s;
		rot->y = (zaxis.x - xaxis.z) * s;
		rot->z = (xaxis.y - yaxis.x) * s;
	}
	else
	{
		// Note: since xaxis, yaxis, and zaxis are normalized, 
		// we will never divide by zero in the code below.
		if (xaxis.x > yaxis.y && xaxis.x > zaxis.z)
		{
			float s = 0.5f / std::sqrt(1.0f + xaxis.x - yaxis.y - zaxis.z);
			rot->w = (yaxis.z - zaxis.y) * s;
			rot->x = 0.25f / s;
			rot->y = (yaxis.x + xaxis.y) * s;
			rot->z = (zaxis.x + xaxis.z) * s;
		}
		else if (yaxis.y > zaxis.z)
		{
			float s = 0.5f / std::sqrt(1.0f + yaxis.y - xaxis.x - zaxis.z);
			rot->w = (zaxis.x - xaxis.z) * s;
			rot->x = (yaxis.x + xaxis.y) * s;
			rot->y = 0.25f / s;
			rot->z = (zaxis.y + yaxis.z) * s;
		}
		else
		{
			float s = 0.5f / std::sqrt(1.0f + zaxis.z - xaxis.x - yaxis.y);
			rot->w = (xaxis.y - yaxis.x) * s;
			rot->x = (zaxis.x + xaxis.z) * s;
			rot->y = (zaxis.y + yaxis.z) * s;
			rot->z = 0.25f / s;
		}
	}

	return true;
}