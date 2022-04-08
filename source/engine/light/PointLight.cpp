#include "PointLight.h"

BEGIN_NAMESPACE
PointLight::PointLight()
{
	m_lightInfo.ambient = RGB(0.05f, 0.05f, 0.05f);
	m_lightInfo.diffuse = RGB(0.8f, 0.8f, 0.8f);
	m_lightInfo.specular = RGB(1.0f, 1.0f, 1.0f);

	m_lightInfo.constant = 1.0f;
	m_lightInfo.linear = 0.09f;
	m_lightInfo.quadratic = 0.032f;
}

PointLight::~PointLight()
{

}

void PointLight::setShaderLightInfo(Shader* shader, int index)
{
	char tempbuf[512];
	sprintf(tempbuf, POINT_LIGHT_POS, index);
	shader->setVec3(tempbuf, this->getWorldPosition());
	sprintf(tempbuf, POINT_LIGHT_AMBIENT, index);
	shader->setRGB(tempbuf, m_lightInfo.ambient);
	sprintf(tempbuf, POINT_LIGHT_DIFFUSE, index);
	shader->setRGB(tempbuf, m_lightInfo.diffuse);
	sprintf(tempbuf, POINT_LIGHT_SPECULAR, index);
	shader->setRGB(tempbuf, m_lightInfo.specular);
	sprintf(tempbuf, POINT_LIGHT_CONSTANT, index);
	shader->setFloat(tempbuf, m_lightInfo.constant);
	sprintf(tempbuf, POINT_LIGHT_LINEAR, index);
	shader->setFloat(tempbuf, m_lightInfo.linear);
	sprintf(tempbuf, POINT_LIGHT_QUADRATIC, index);
	shader->setFloat(tempbuf, m_lightInfo.quadratic);
}

END_NAMESPACE