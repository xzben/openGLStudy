#ifndef __2022_03_31_SPOT_LIGHT_H__
#define __2022_03_31_SPOT_LIGHT_H__

#include "light/Light.h"
#include "math/Vec3.h"
#include "base/Shader.h"
BEGIN_NAMESPACE

struct SpotLightShaderData
{
	fVec3	 direction;  //聚光灯的朝向
	float	 cutOff;     //聚光灯内圈
	float    outerCutOff; //聚光灯外圈， 内外圈主要是软化光线从亮到暗的过度

	RGB		 ambient;
	RGB		 diffuse;
	RGB		 specular;

	float		constant;  //点光源 衰减参数 常量
	float		linear;    //点光源 衰减参数 一次线性常量
	float		quadratic; //点光源 衰减参数 二次常量
};

class SpotLight : public Light
{
protected:
	friend class LightManager;
	SpotLightShaderData m_lightInfo;
public:
	CREATE_FUNC(SpotLight);
	SpotLight();
	virtual ~SpotLight();
	virtual void setShaderLightInfo(Shader* shader, int index);

	void setDirection(fVec3& value) { m_lightInfo.direction = value; }
	void setRange(float minAngle, float maxAngle) 
	{ 
		m_lightInfo.cutOff = cos(CC_DEGREES_TO_RADIANS(minAngle)); 
		m_lightInfo.outerCutOff = cos(CC_DEGREES_TO_RADIANS(maxAngle)); 
	}

	void setAmbient(RGB& value) { m_lightInfo.ambient = value; }
	void setDiffuse(RGB& value) { m_lightInfo.diffuse = value; }
	void setSpecular(RGB& value) { m_lightInfo.specular = value; }
	void setLightConstant(float constant, float linear, float quadratic)
	{
		m_lightInfo.constant = constant;
		m_lightInfo.linear = linear;
		m_lightInfo.quadratic = quadratic;
	}
};

END_NAMESPACE
#endif//__2022_03_31_SPOT_LIGHT_H__