#include "DirectionLight.h"

BEGIN_NAMESPACE

void DirectionLight::setShaderLightInfo(Shader* shader, int index)
{
	auto lightinfo = m_lightInfo;

	shader->setVec3(DIRECT_LIGHT_DIRECT, lightinfo.direction);
	shader->setRGB(DIRECT_LIGHT_AMBIENT, lightinfo.ambient);
	shader->setRGB(DIRECT_LIGHT_DIFFUSE, lightinfo.diffuse);
	shader->setRGB(DIRECT_LIGHT_SPECULAR, lightinfo.specular);
}


DirectionLight::DirectionLight()
{
	m_lightInfo.direction = fVec3(-0.2f, -1.0f, -0.3f);

	m_lightInfo.ambient = RGB(0.5f, 0.5f, 0.5f);
	m_lightInfo.diffuse = RGB(0.4f, 0.4f, 0.4f);
	m_lightInfo.specular = RGB(0.5f, 0.5f, 0.5f);
}

DirectionLight::~DirectionLight()
{

}

END_NAMESPACE