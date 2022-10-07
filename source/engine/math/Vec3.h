#ifndef __2022_01_04_VEC3_H__
#define __2022_01_04_VEC3_H__

#include <cmath>
#include "define.h"

BEGIN_NAMESPACE

template<class TYPENAME>
class Vec3
{
public:
	TYPENAME x;
	TYPENAME y;
	TYPENAME z;
public:
	Vec3() {
		x = y = z = 0;
	}

	Vec3(TYPENAME x, TYPENAME y, TYPENAME z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3(const Vec3<TYPENAME>& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	void operator+(const TYPENAME v) {
		this->x += v;
		this->y += v;
		this->z += v;
	}

	void operator-(const TYPENAME v) {
		this->x -= v;
		this->y -= v;
		this->z -= v;
	}

	Vec3<TYPENAME> operator-(const Vec3<TYPENAME>& v) const
	{
		Vec3 result;
		result.x = this->x - v.x;
		result.y = this->y - v.y;
		result.z = this->z - v.z;

		return result;
	}

	void normalize() 
	{
		float n = x * x + y * y + z * z;
		if (n == 1) return;

		n = std::sqrt(n);

		if (n < MATH_TOLERANCE)
			return;

		n = 1.0f / n;

		x *= n;
		y *= n;
		z *= n;
	}

	TYPENAME getLen() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	//点乘 V1*V2 = |V1||V2|cos@
	TYPENAME dot(const Vec3<TYPENAME>& rvalue) const
	{
		return x* rvalue.x + y * rvalue.y + z * rvalue.z;
	}

	//差乘 V1xV2 = V3 V3 与 V1 V2 都垂直
	Vec3<TYPENAME> cross(const Vec3<TYPENAME>& rvalue) const
	{
		Vec3<TYPENAME> resutl;

		resutl.x = y * rvalue.z - z * rvalue.y;
		resutl.y = z * rvalue.x - x * rvalue.z;
		resutl.z = x * rvalue.y - y * rvalue.x;

		return resutl;
	}
};


typedef Vec3<float>		fVec3;
typedef Vec3<int>		iVec3;
typedef Vec3<float>		POSITION;

END_NAMESPACE

#endif//__2022_01_04_VEC3_H__