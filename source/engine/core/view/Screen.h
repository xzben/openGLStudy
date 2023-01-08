#pragma once

#include "common.h"
#include "core/math/math.h"
BEGIN_OGS_NAMESPACE

class Screen : public Object
{
	DECLARE_CLASS(Screen)
public:
	Screen();

	static const Rect& getViewport();
	static void setViewport(const Rect& viewport);
	static Size getSize();
protected:
	static Rect m_viewport;
};
END_OGS_NAMESPACE