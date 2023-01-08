#ifndef __2022_03_31_DIRECTION_LIGHT_H__
#define __2022_03_31_DIRECTION_LIGHT_H__

#include "light/Light.h"
#include "math/Vec3.h"
#include "base/Shader.h"

BEGIN_NAMESPACE

struct DirectionLightShaderData
{
	fVec3    direction;
	RGB		 ambient;
	RGB		 diffuse;
	RGB		 specular;
};

class DirectionLight : public Light
{
protected:
	friend class LightManager;
	DirectionLightShaderData m_lightInfo;
public:
	CREATE_FUNC(DirectionLight);
	DirectionLight();
	virtual ~DirectionLight();
	virtual void setShaderLightInfo(Shader* shader, int index);

	void setDirect(fVec3& direct) { m_lightInfo.direction = direct; }
	void setAmbient(RGB& value) { m_lightInfo.ambient = value; }
	void setDiffuse(RGB& value) { m_lightInfo.diffuse = value; }
	void setSpecular(RGB& value) { m_lightInfo.specular = value; }
};

END_NAMESPACE
#endif//__2022_03_31_DIRECTION_LIGHT_H__