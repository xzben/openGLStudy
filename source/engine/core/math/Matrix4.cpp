#include "Matrix4.h"
#include "Vector3.h"
#include "Quaterion.h"
BEGIN_OGS_NAMESPACE

const Matrix4 Matrix4::Identity;

Matrix4::Matrix4()
{
	memset(values, 0, sizeof(values));
	_11 = _22 = _33 = _44 = 1.0f;
}

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
				 float m21, float m22, float m23, float m24,
				 float m31, float m32, float m33, float m34,
				 float m41, float m42, float m43, float m44)
	:_11(m11), _12(m12), _13(m13), _14(m14)
	,_21(m21), _22(m22), _23(m23), _24(m24)
	,_31(m31), _32(m32), _33(m33), _34(m34)
	,_41(m41), _42(m42), _43(m43), _44(m44)
{

}

float Matrix4::determinant() const
{
	const float* m = values;
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

bool Matrix4::decompose(Vector3* trans, Vector3* sc, Quaterion* rot) const
{
	if (trans)
	{
		trans->x = _14;
		trans->y = _24;
		trans->z = _34;
	}

	if (sc == nullptr && rot == nullptr) return true;

	Vector3 xaxis(_11, _21, _31);
	float scalex = xaxis.length();
	Vector3 yaxis(_12, _22, _32);
	float scaley = yaxis.length();
	Vector3 zaxis(_13, _23, _33);
	float scalez = zaxis.length();

	float det = determinant();
	if (det < 0)
		scalez = -scalez;

	if (sc)
	{
		sc->x = scalex;
		sc->y = scaley;
		sc->z = scalez;
	}

	if (rot == nullptr)
		return true;

	if (scalex < MATH_TOLERANCE || scaley < MATH_TOLERANCE || std::abs(scalez) < MATH_TOLERANCE)
		return false;

	float rn;

	rn = 1.0f / scalex;

	xaxis.x *= rn;
	xaxis.y *= rn;
	xaxis.z *= rn;

	rn = 1.0f / scaley;

	yaxis.x *= rn;
	yaxis.y *= rn;
	yaxis.z *= rn;

	rn = 1.0f / scalez;

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

Matrix4 Matrix4::lookAt(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	//根据 摄像机的位置和目标点计算摄像机的方向向量
	Vector3 direct = pos - target;
	direct.normalize();
	// 根据上向量 和 方向向量 叉乘 得到 与之两两垂直的右向量
	Vector3 cameraRight = up.cross(direct);
	cameraRight.normalize();

	//根据方向向量和右向量计算得到 两两相互垂直的 摄像机的上向量，至此三个相互垂直的坐标系统 x,y,z 三个轴向量都得到了
	Vector3 cameraUp = direct.cross(cameraRight);
	cameraUp.normalize();

	const Vector3& R = cameraRight;
	const Vector3& U = cameraUp;
	const Vector3& D = direct;
	const Vector3& P = pos;

	return Matrix4( R.x, R.y, R.z, -R.x * P.x - R.y * P.y - R.z * P.z,
					U.x, U.y, U.z, -U.x * P.x - U.y * P.y - U.z * P.z,
					D.x, D.y, D.z, -D.x * P.x - D.y * P.y - D.z * P.z,
					0,	 0,   0,   1);
}

Matrix4 Matrix4::translate(const Vector3& tans)
{
	return Matrix4(1, 0, 0, tans.x,
		0, 1, 0, tans.y,
		0, 0, 1, tans.z,
		0, 0, 0, 1);
	

}

Matrix4 Matrix4::scale(const Vector3& sc)
{
	return Matrix4(sc.x, 0, 0, 0,
				      0, sc.y, 0, 0,
					  0, 0, sc.z, 0,
					  0, 0, 0, 1);
}

Matrix4 Matrix4::rotation(const Vector3& rot)
{
	Quaterion _rotationQuat;

	float halfRadx = CC_DEGREES_TO_RADIANS(rot.x / 2.f), halfRady = CC_DEGREES_TO_RADIANS(rot.y / 2.f), halfRadz = -CC_DEGREES_TO_RADIANS(rot.z / 2.f);
	float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
	_rotationQuat.x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
	_rotationQuat.y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
	_rotationQuat.z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
	_rotationQuat.w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;

	return rotation(_rotationQuat);
}

Matrix4 Matrix4::rotation(const Quaterion& q)
{
	Matrix4 dst;
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

	dst.values[0] = 1.0f - yy2 - zz2;
	dst.values[1] = xy2 + wz2;
	dst.values[2] = xz2 - wy2;
	dst.values[3] = 0.0f;

	dst.values[4] = xy2 - wz2;
	dst.values[5] = 1.0f - xx2 - zz2;
	dst.values[6] = yz2 + wx2;
	dst.values[7] = 0.0f;

	dst.values[8] = xz2 + wy2;
	dst.values[9] = yz2 - wx2;
	dst.values[10] = 1.0f - xx2 - yy2;
	dst.values[11] = 0.0f;

	dst.values[12] = 0.0f;
	dst.values[13] = 0.0f;
	dst.values[14] = 0.0f;
	dst.values[15] = 1.0f;

	return (dst);
}

Matrix4 Matrix4::perspective(float fieldOfView, float aspectRatio, float znear, float zfar)
{
	CC_ASSERT(znear != zfar);
	Matrix4 result;
	float f_n = 1.0f / (zfar - znear);
	float theta = CC_DEGREES_TO_RADIANS(fieldOfView) * 0.5f;
	if (std::abs(std::fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
	{
		CCLOG_ERROR("Invalid field of view value (%f) causes attempted calculation tan(%f), which is undefined.", fieldOfView, theta);
		return std::move(result);
	}
	float divisor = std::tan(theta);
	CC_ASSERT(divisor);
	float factor = 1.0f / divisor;

	memset(result.values, 0, sizeof(float)*16);

	CC_ASSERT(aspectRatio);
	result.values[0] = (1.0f / aspectRatio) * factor;
	result.values[5] = factor;
	result.values[10] = (-(zfar + znear)) * f_n;
	result.values[11] = -1.0f;
	result.values[14] = -2.0f * zfar * znear * f_n;

	return (result);
}

Matrix4 Matrix4::orthograhic(float width, float height, float znear, float zfar)
{
	float halfWidth = width / 2.0f;
	float halfHeight = height / 2.0f;
	return orthograhic(-halfWidth, halfHeight, -halfHeight, halfHeight, znear, zfar);
}

Matrix4 Matrix4::orthograhic(float left, float right, float bottom, float top, float znear, float zfar)
{
	CC_ASSERT(right != left);
	CC_ASSERT(top != bottom);
	CC_ASSERT(zfar != znear);

	Matrix4 result;


	result.values[0] = 2 / (right - left);
	result.values[1] = 0.0f;
	result.values[2] = 0.0f;
	result.values[3] = 0.0f;
		   
	result.values[4] = 0.0f;
	result.values[5] = 2 / (top - bottom);
	result.values[6] = 0.0f;
	result.values[7] = 0.0f;
		   
	result.values[8] = 0.0f;
	result.values[9] = 0.0f;
	result.values[10] = 2 / (znear - zfar);
	result.values[11] = 0.0f;
		   
	result.values[12] = (left + right) / (left - right);
	result.values[13] = (top + bottom) / (bottom - top);
	result.values[14] = (znear + zfar) / (znear - zfar);
	result.values[15] = 1.0f;

	return (result);
}

const Matrix4& Matrix4::operator+=(const float v)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] += v;
	}

	return *this;
}
const Matrix4& Matrix4::operator-=(const float v)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] -= v;
	}

	return *this;
}
const Matrix4& Matrix4::operator*=(const float v)
{
	for (int i = 0; i < 16; i++)
	{
		values[i] *= v;
	}

	return *this;
}

Matrix4 Matrix4::operator+(const float v)
{
	Matrix4 r;
	for (int i = 0; i < 16; i++)
	{
		r.values[i] = values[i] + v;
	}

	return r;
}

Matrix4 Matrix4::operator-(const float v)
{
	Matrix4 r;
	for (int i = 0; i < 16; i++)
	{
		r.values[i] = values[i] - v;
	}

	return r;
}

Matrix4 Matrix4::operator*(const float v)
{
	Matrix4 r;
	for (int i = 0; i < 16; i++)
	{
		r.values[i] = values[i] * v;
	}

	return r;
}

const Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	Matrix4 result = *this * (rhs);

	memcpy(values, result.values, sizeof(float) * 16);

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs)
{
	Matrix4 result;

	result.values[0] = values[0] * rhs.values[0] + values[4] * rhs.values[1] + values[8] * rhs.values[2] + values[12] * rhs.values[3];
	result.values[4] = values[0] * rhs.values[4] + values[4] * rhs.values[5] + values[8] * rhs.values[6] + values[12] * rhs.values[7];
	result.values[8] = values[0] * rhs.values[8] + values[4] * rhs.values[9] + values[8] * rhs.values[10] + values[12] * rhs.values[11];
	result.values[12] = values[0] * rhs.values[12] + values[4] * rhs.values[13] + values[8] * rhs.values[14] + values[12] * rhs.values[15];

	result.values[1] = values[1] * rhs.values[0] + values[5] * rhs.values[1] + values[9] * rhs.values[2] + values[13] * rhs.values[3];
	result.values[5] = values[1] * rhs.values[4] + values[5] * rhs.values[5] + values[9] * rhs.values[6] + values[13] * rhs.values[7];
	result.values[9] = values[1] * rhs.values[8] + values[5] * rhs.values[9] + values[9] * rhs.values[10] + values[13] * rhs.values[11];
	result.values[13] = values[1] * rhs.values[12] + values[5] * rhs.values[13] + values[9] * rhs.values[14] + values[13] * rhs.values[15];

	result.values[2] = values[2] * rhs.values[0] + values[6] * rhs.values[1] + values[10] * rhs.values[2] + values[14] * rhs.values[3];
	result.values[6] = values[2] * rhs.values[4] + values[6] * rhs.values[5] + values[10] * rhs.values[6] + values[14] * rhs.values[7];
	result.values[10] = values[2] * rhs.values[8] + values[6] * rhs.values[9] + values[10] * rhs.values[10] + values[14] * rhs.values[11];
	result.values[14] = values[2] * rhs.values[12] + values[6] * rhs.values[13] + values[10] * rhs.values[14] + values[14] * rhs.values[15];

	result.values[3] = values[3] * rhs.values[0] + values[7] * rhs.values[1] + values[11] * rhs.values[2] + values[15] * rhs.values[3];
	result.values[7] = values[3] * rhs.values[4] + values[7] * rhs.values[5] + values[11] * rhs.values[6] + values[15] * rhs.values[7];
	result.values[11] = values[3] * rhs.values[8] + values[7] * rhs.values[9] + values[11] * rhs.values[10] + values[15] * rhs.values[11];
	result.values[15] = values[3] * rhs.values[12] + values[7] * rhs.values[13] + values[11] * rhs.values[14] + values[15] * rhs.values[15];

	return result;
}

Vector3 Matrix4::operator*(const Vector3& rhs)
{
	Vector3 result;
	Vector4 rvalue(rhs.x, rhs.y, rhs.z, 1);

	result.x = values[0] * rvalue.x + values[4] * rvalue.y + values[8] * rvalue.z + values[12] * rvalue.w;
	result.y = values[1] * rvalue.x + values[5] * rvalue.y + values[9] * rvalue.z + values[13] * rvalue.w;
	result.z = values[2] * rvalue.x + values[6] * rvalue.y + values[10] * rvalue.z + values[14] * rvalue.w;

	return result;
}

Vector4 Matrix4::operator*(const Vector4& rvalue)
{
	Vector4 result;

	result.x = values[0] * rvalue.x + values[4] * rvalue.y + values[8] * rvalue.z + values[12] * rvalue.w;
	result.y = values[1] * rvalue.x + values[5] * rvalue.y + values[9] * rvalue.z + values[13] * rvalue.w;
	result.z = values[2] * rvalue.x + values[6] * rvalue.y + values[10] * rvalue.z + values[14] * rvalue.w;
	result.w = values[3] * rvalue.x + values[7] * rvalue.y + values[11] * rvalue.z + values[15] * rvalue.w;

	return result;
}

Matrix4 Matrix4::transpose()const //矩阵转置
{
	Matrix4 result;

	result.values[0] = values[0];
	result.values[1] = values[4];
	result.values[2] = values[8];
	result.values[3] = values[12];

	result.values[4] = values[1];
	result.values[5] = values[5];
	result.values[6] = values[9];
	result.values[7] = values[13];

	result.values[8] = values[2];
	result.values[9] = values[6];
	result.values[10] = values[10];
	result.values[11] = values[14];

	result.values[12] = values[3];
	result.values[13] = values[7];
	result.values[14] = values[11];
	result.values[15] = values[15];

	return result;
}

Matrix4 Matrix4::inverse()const //矩阵的逆
{
	Matrix4 result;

	float a0 = values[0] * values[5] - values[1] * values[4];
	float a1 = values[0] * values[6] - values[2] * values[4];
	float a2 = values[0] * values[7] - values[3] * values[4];
	float a3 = values[1] * values[6] - values[2] * values[5];
	float a4 = values[1] * values[7] - values[3] * values[5];
	float a5 = values[2] * values[7] - values[3] * values[6];
	float b0 = values[8] * values[13] - values[9] * values[12];
	float b1 = values[8] * values[14] - values[10] * values[12];
	float b2 = values[8] * values[15] - values[11] * values[12];
	float b3 = values[9] * values[14] - values[10] * values[13];
	float b4 = values[9] * values[15] - values[11] * values[13];
	float b5 = values[10] * values[15] - values[11] * values[14];

	float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	if (std::abs(det) <= MATH_TOLERANCE)
		return result;

	result.values[0] = values[5] * b5 - values[6] * b4 + values[7] * b3;
	result.values[1] = -values[1] * b5 + values[2] * b4 - values[3] * b3;
	result.values[2] = values[13] * a5 - values[14] * a4 + values[15] * a3;
	result.values[3] = -values[9] * a5 + values[10] * a4 - values[11] * a3;
		   
	result.values[4] = -values[4] * b5 + values[6] * b2 - values[7] * b1;
	result.values[5] = values[0] * b5 - values[2] * b2 + values[3] * b1;
	result.values[6] = -values[12] * a5 + values[14] * a2 - values[15] * a1;
	result.values[7] = values[8] * a5 - values[10] * a2 + values[11] * a1;
		   
	result.values[8] = values[4] * b4 - values[5] * b2 + values[7] * b0;
	result.values[9] = -values[0] * b4 + values[1] * b2 - values[3] * b0;
	result.values[10] = values[12] * a4 - values[13] * a2 + values[15] * a0;
	result.values[11] = -values[8] * a4 + values[9] * a2 - values[11] * a0;
		   
	result.values[12] = -values[4] * b3 + values[5] * b1 - values[6] * b0;
	result.values[13] = values[0] * b3 - values[1] * b1 + values[2] * b0;
	result.values[14] = -values[12] * a3 + values[13] * a1 - values[14] * a0;
	result.values[15] = values[8] * a3 - values[9] * a1 + values[10] * a0;

	result = result * (1 / det);

	return result;
}

END_OGS_NAMESPACE