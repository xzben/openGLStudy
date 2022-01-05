#ifndef __2022_01_04_MATH_RECT_H__
#define __2022_01_04_MATH_RECT_H__

class Rect
{
public:
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
public:
	Rect() {};
	Rect(float x, float y, float width, float height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};
#endif//__2022_01_04_MATH_RECT_H__