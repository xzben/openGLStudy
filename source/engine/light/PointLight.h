#ifndef __2022_03_31_POINT_LIGHT_H__
#define __2022_03_31_POINT_LIGHT_H__

#include "light/Light.h"
#include "base/Shader.h"
BEGIN_NAMESPACE

struct PointLightShaderData
{
	RGB		 ambient;
	RGB		 diffuse;
	RGB		 specular;

	float		constant;  //点光源 衰减参数 常量
	float		linear;    //点光源 衰减参数 一次线性常量
	float		quadratic; //点光源 衰减参数 二次常量
};

class PointLight : public Light
{
protected:
	friend class LightManager;
	PointLightShaderData m_lightInfo;
public:
	CREATE_FUNC(PointLight);
	PointLight();
	virtual ~PointLight();
	virtual void setShaderLightInfo(Shader* shader, int index);


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
#endif//__2022_03_31_POINT_LIGHT_H__