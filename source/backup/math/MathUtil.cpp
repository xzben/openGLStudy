#include "MathUtil.h"
#include "quaternion.h"
#include <cmath>
#include "common.h"

BEGIN_NAMESPACE


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

const fMat4& MathUtil::IdentityMat4()
{
	static fMat4 identity;

	return identity;
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

	return (dst);

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


//
fMat4 MathUtil::lookAt(const fVec3& pos, const fVec3& target, const fVec3& up)
{
	//根据 摄像机的位置和目标点计算摄像机的方向向量
	fVec3 direct = pos - target;
	direct.normalize();
	// 根据上向量 和 方向向量 叉乘 得到 与之两两垂直的右向量
	fVec3 cameraRight = up.cross(direct);
	cameraRight.normalize();

	//根据方向向量和右向量计算得到 两两相互垂直的 摄像机的上向量，至此三个相互垂直的坐标系统 x,y,z 三个轴向量都得到了
	fVec3 cameraUp = direct.cross(cameraRight);
	cameraUp.normalize();

	const fVec3& R = cameraRight;
	const fVec3& U = cameraUp;
	const fVec3& D = direct;
	const fVec3& P = pos;

	fMat4 view(	R.x, R.y, R.z, -R.x * P.x - R.y * P.y - R.z * P.z,
				U.x, U.y, U.z, -U.x * P.x - U.y * P.y - U.z * P.z,
				D.x, D.y, D.z, -D.x * P.x - D.y * P.y - D.z * P.z,
				  0,   0,   0, 1);

	return view;
}

fMat4 MathUtil::cameraLookAt(const fVec3& pos, const fVec3& rot, const fVec3& up)
{
	fVec3 direct(0.0f, 0.0f, -1.0f);
	direct = MathUtil::translate(pos) * MathUtil::rotation(rot) * direct;

	direct.normalize();
	
	fVec3 cameraRight = up.cross(direct);
	cameraRight.normalize();

	//根据方向向量和右向量计算得到 两两相互垂直的 摄像机的上向量，至此三个相互垂直的坐标系统 x,y,z 三个轴向量都得到了
	fVec3 cameraUp = direct.cross(cameraRight);
	cameraUp.normalize();

	const fVec3& R = cameraRight;
	const fVec3& U = cameraUp;
	const fVec3& D = direct;
	const fVec3& P = pos;

	fMat4 view(R.x, R.y, R.z, -R.x * P.x - R.y * P.y - R.z * P.z,
		U.x, U.y, U.z, -U.x * P.x - U.y * P.y - U.z * P.z,
		D.x, D.y, D.z, -D.x * P.x - D.y * P.y - D.z * P.z,
		0.0f, 0.0f, 0.0f, 1.0f);

	return view;
}


fMat4 MathUtil::createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane)
{
	CC_ASSERT(zNearPlane != zFarPlane);
	fMat4 result;
	float f_n = 1.0f / (zFarPlane - zNearPlane);
	float theta = MATH_DEG_TO_RAD(fieldOfView) * 0.5f;
	if (std::abs(std::fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
	{
		CCLOG_ERROR("Invalid field of view value (%f) causes attempted calculation tan(%f), which is undefined.", fieldOfView, theta);
		return std::move(result);
	}
	float divisor = std::tan(theta);
	CC_ASSERT(divisor);
	float factor = 1.0f / divisor;

	memset(result.m_data, 0, MATRIX_SIZE);

	CC_ASSERT(aspectRatio);
	result.m_data[0] = (1.0f / aspectRatio) * factor;
	result.m_data[5] = factor;
	result.m_data[10] = (-(zFarPlane + zNearPlane)) * f_n;
	result.m_data[11] = -1.0f;
	result.m_data[14] = -2.0f * zFarPlane * zNearPlane * f_n;

	return (result);
}

fMat4 MathUtil::createOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	return createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane);
}

fMat4 MathUtil::createOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
	CC_ASSERT(right != left);
	CC_ASSERT(top != bottom);
	CC_ASSERT(zFarPlane != zNearPlane);

	fMat4 result;

	
	result.m_data[0] = 2 / (right - left);
	result.m_data[1] = 0.0f;
	result.m_data[2] = 0.0f;
	result.m_data[3] = 0.0f;

	result.m_data[4] = 0.0f;
	result.m_data[5] = 2 / (top - bottom);
	result.m_data[6] = 0.0f;
	result.m_data[7] = 0.0f;

	result.m_data[8] = 0.0f;
	result.m_data[9] = 0.0f;
	result.m_data[10] = 2 / (zNearPlane - zFarPlane);
	result.m_data[11] = 0.0f;

	result.m_data[12] = (left + right) / (left - right);
	result.m_data[13] = (top + bottom) / (bottom - top);
	result.m_data[14] = (zNearPlane + zFarPlane) / (zNearPlane - zFarPlane);
	result.m_data[15] = 1.0f;

	return (result);
}

END_NAMESPACE