#include "LightManager.h"
#include "base/Shader.h"

BEGIN_NAMESPACE

void LightManager::setShaderLightInfo(Shader* shader)
{
	iVec3 lightNums = getLightNums();
	shader->setVec3(LIGHT_NUM, lightNums);
	
	if (m_directLight)
	{
		m_directLight->setShaderLightInfo(shader, 0);
	}

	for (int i = 0; i < lightNums.y; i++)
	{
		PointLight* light = m_pointLights.at(i);
		light->setShaderLightInfo(shader, i);
	}

	for (int i = 0; i < lightNums.z; i++)
	{
		SpotLight* light = m_spotLights.at(i);
		light->setShaderLightInfo(shader, i);
	}
}

iVec3 LightManager::getLightNums()
{
	iVec3 nums;
	nums.x = m_directLight == nullptr ? 0 : 1;
	nums.y = m_pointLights.size();
	nums.z = m_spotLights.size();

	return nums;
}

void LightManager::addLight(Light* light)
{
	DirectionLight* dlight = dynamic_cast<DirectionLight*>(light);
	if (dlight != nullptr) {
		return this->addDirectLigth(dlight);
	}

	PointLight* plight = dynamic_cast<PointLight*>(light);
	if (plight != nullptr) {
		return this->addPointLight(plight);
	}

	SpotLight* slight = dynamic_cast<SpotLight*>(light);
	if (slight != nullptr) {
		return this->addSpotLight(slight);
	}
}

void LightManager::addDirectLigth(DirectionLight* dlight)
{
	CC_ASSERT(m_directLight == nullptr);

	m_directLight = dlight;
}

void LightManager::addPointLight(PointLight* plight)
{
	m_pointLights.push_back(plight);
}

void LightManager::addSpotLight(SpotLight* splight)
{
	m_spotLights.push_back(splight);
}

void LightManager::removeLight(Light* light)
{
	DirectionLight* dlight = dynamic_cast<DirectionLight*>(light);
	if (dlight != nullptr) {
		return this->removeDirectLight(dlight);
	}

	PointLight* plight = dynamic_cast<PointLight*>(light);
	if (plight != nullptr) {
		return this->removePointLight(plight);
	}

	SpotLight* slight = dynamic_cast<SpotLight*>(light);
	if (slight != nullptr) {
		return this->removeSpotLight(slight);
	}
}

void LightManager::removeDirectLight(DirectionLight* dlight)
{
	if (this->m_directLight == dlight) {
		this->m_directLight = nullptr;
	}
}

void LightManager::removePointLight(PointLight* plight)
{
	for (auto it = m_pointLights.begin(); it != m_pointLights.end(); it++)
	{
		if (*it == plight)
		{
			m_pointLights.erase(it);
			break;
		}
	}
}

void LightManager::removeSpotLight(SpotLight* splight)
{
	for (auto it = m_spotLights.begin(); it != m_spotLights.end(); it++)
	{
		if (*it == splight)
		{
			m_spotLights.erase(it);
			break;
		}
	}
}

END_NAMESPACE