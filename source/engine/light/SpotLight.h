#ifndef __2022_03_31_SPOT_LIGHT_H__
#define __2022_03_31_SPOT_LIGHT_H__

#include "light/Light.h"
#include "math/Vec3.h"
#include "base/Shader.h"
BEGIN_NAMESPACE

struct SpotLightShaderData
{
	fVec3	 direction;  //�۹�Ƶĳ���
	float	 cutOff;     //�۹����Ȧ
	float    outerCutOff; //�۹����Ȧ�� ����Ȧ��Ҫ�������ߴ��������Ĺ���

	RGB		 ambient;
	RGB		 diffuse;
	RGB		 specular;

	float		constant;  //���Դ ˥������ ����
	float		linear;    //���Դ ˥������ һ�����Գ���
	float		quadratic; //���Դ ˥������ ���γ���
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