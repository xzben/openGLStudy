#include "SpotLight.h"

BEGIN_NAMESPACE

SpotLight::SpotLight()
{
	setRange(12.5f, 15.0f);
	m_lightInfo.direction = fVec3(0.0f, 0.0f, -1.0f);
	m_lightInfo.ambient = RGB(0.0f, 0.0f, 0.0f);
	m_lightInfo.diffuse = RGB(1.0f, 1.0f, 1.0f);
	m_lightInfo.specular = RGB(1.0f, 1.0f, 1.0f);

	m_lightInfo.constant = 1.0f;
	m_lightInfo.linear = 0.09f;
	m_lightInfo.quadratic = 0.032f;
}

SpotLight::~SpotLight()
{

}

void SpotLight::setShaderLightInfo(Shader* shader, int index)
{
	char tempbuf[512];
	sprintf(tempbuf, SPOT_LIGHT_POS, index);
	shader->setVec3(tempbuf, this->getWorldPosition());

	sprintf(tempbuf, SPOT_LIGHT_DIRECT, index);
	shader->setVec3(tempbuf, m_lightInfo.direction);

	sprintf(tempbuf, SPOT_LIGHT_CUTOFF, index);
	shader->setFloat(tempbuf, m_lightInfo.cutOff);

	sprintf(tempbuf, SPOT_LIGHT_OUTERCUTOFF, index);
	shader->setFloat(tempbuf, m_lightInfo.outerCutOff);

	sprintf(tempbuf, SPOT_LIGHT_AMBIENT, index);
	shader->setRGB(tempbuf, m_lightInfo.ambient);

	sprintf(tempbuf, SPOT_LIGHT_DIFFUSE, index);
	shader->setRGB(tempbuf, m_lightInfo.diffuse);

	sprintf(tempbuf, SPOT_LIGHT_SPECULAR, index);
	shader->setRGB(tempbuf, m_lightInfo.specular);

	sprintf(tempbuf, SPOT_LIGHT_CONSTANT, index);
	shader->setFloat(tempbuf, m_lightInfo.constant);

	sprintf(tempbuf, SPOT_LIGHT_LINEAR, index);
	shader->setFloat(tempbuf, m_lightInfo.linear);

	sprintf(tempbuf, SPOT_LIGHT_QUADRATIC, index);
	shader->setFloat(tempbuf, m_lightInfo.quadratic);
}

END_NAMESPACE