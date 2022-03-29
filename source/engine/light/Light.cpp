#include "light/Light.h"

BEGIN_NAMESPACE

Light::Light()
	:m_ambientStrength(0.1)
{

}

Light::~Light()
{

}

void Light::setLightColor(const Color& color)
{
	m_lightColor = color;
}
const Color& Light::getLightColor()
{
	return m_lightColor;
}

POSITION Light::getLightPos()
{
	return this->getWorldPosition();
}

END_NAMESPACE

