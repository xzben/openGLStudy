#ifndef __2022_01_04_MATH_SIZE_H__
#define __2022_01_04_MATH_SIZE_H__

#include "define.h"

BEGIN_NAMESPACE

class Size
{
public:
	float width = 0;
	float height = 0;
public:
	Size(){}
	Size(float width, float height) {
		this->width = width;
		this->height = height;
	}
};

END_NAMESPACE

#endif//__2022_01_04_MATH_SIZE_H__