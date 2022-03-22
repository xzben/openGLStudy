#ifndef __2022_01_04_VEC2_H__
#define __2022_01_04_VEC2_H__
#include "common.h"

BEGIN_NAMESPACE

template<class TYPENAME>
class Vec2
{
public:
	TYPENAME x;
	TYPENAME y;
public:
	Vec2() {

	}
	Vec2(TYPENAME x, TYPENAME y)
	{
		this->x = x;
		this->y = y;
	}
};


typedef Vec2<float>		fVec2;
typedef Vec2<int>		iVec2;

END_NAMESPACE

#endif//__2022_01_04_VEC2_H__