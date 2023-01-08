#pragma once

#include "define.h"
#include "Size.h"
BEGIN_OGS_NAMESPACE

class Rect
{
public:
	union
	{
		struct 
		{
			float x, y, width, height;
		};

		float values[4];
	};

	Rect()
	{
		memset(values, 0, sizeof(float) * 4);
	}

	Rect(float xx, float yy, float w, float h)
		:x(xx), y(yy), width(w), height(h)
	{
	}

	Size getSize() const
	{
		return Size(width, height);
	}

	bool operator==(const Rect& rhs) const
	{
		return rhs.x == x && rhs.y == y && rhs.width == width && rhs.height == height;
	}
};
END_OGS_NAMESPACE