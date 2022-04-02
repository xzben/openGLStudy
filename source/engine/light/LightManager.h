#ifndef __2022_04_01_LIGHT_MANAGER_H__
#define __2022_04_01_LIGHT_MANAGER_H__

#include "common.h"
#include "base/InstanceBase.h"
#include "light/DirectionLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"

BEGIN_NAMESPACE

class Shader;

class LightManager : public InstanceBase<LightManager>
{
protected:
	std::vector<DirectionLight*> m_directLights;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*>  m_spotLights;

public:
	void setShaderLightInfo(Shader* shader);
};

END_NAMESPACE
#endif//__2022_04_01_LIGHT_MANAGER_H__