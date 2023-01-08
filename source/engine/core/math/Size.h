#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE

class Size
{
public:
	float width{0.f};
	float height{0.f};
	Size(){}

	Size(float w, float h)
	{
		width = w;
		height = h;
	}

	bool operator==(const Size& rhs) const
	{
		return rhs.width == width && rhs.height == height;
	}
};

END_OGS_NAMESPACE