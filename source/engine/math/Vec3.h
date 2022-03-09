#ifndef __2022_01_04_VEC3_H__
#define __2022_01_04_VEC3_H__

#include <math.h>

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

	TYPENAME getLen() {
		return sqrt(x * x + y * y + z * z);
	}

	TYPENAME dot(const Vec3<TYPENAME>& rvalue) {
		return x* rvalue.x + y * rvalue.y + z * rvalue.z;
	}

	Vec3<TYPENAME> cross(const Vec3<TYPENAME>& rvalue) {
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
typedef Vec3<short>		RGB;

#endif//__2022_01_04_VEC3_H__