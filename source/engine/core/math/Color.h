#pragma once
#include "define.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class Color
{
	DECLARE_CLASS_BASE(Color)
	DECLARE_REFLEX_CLASS_FIELD(Color)

public:
	static const Color  WHITE;
	static const Color  BLACK;
	static const Color  RED;
	static const Color  GREEN;
	static const Color  BLUE;
	static const Color  GRAY;
public:
	union
	{
		struct {
			float r, g, b, a;
		};

		float value[4];
	};

	Color()
	{
		value[0] = value[1] = value[2] = value[3] = 255.f;
	}

	Color(float rr, float gg, float bb, float aa)
		: r(rr), g(gg), b(bb), a(aa)
	{

	}

	Color(const Color& r)
	{
		memcpy(value, r.value, sizeof(float) * 4);
	}
};

END_OGS_NAMESPACE