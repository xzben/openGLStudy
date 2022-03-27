#ifndef __2022_03_25_LIGHT_H__
#define __2022_03_25_LIGHT_H__

#include "common.h"
#include "base/Node.h"
#include "render/Color.h"
#include "math/Vec3.h"

BEGIN_NAMESPACE

class Light : public Node
{
protected:
	Color m_lightColor;
public:
	Light();
	virtual ~Light();

	void setLightColor(const Color& color);
	const Color& getLightColor();
	POSITION getLightPos();
};

END_NAMESPACE
#endif//__2022_03_25_LIGHT_H__