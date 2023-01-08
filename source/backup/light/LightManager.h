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
	DirectionLight* m_directLight;
	std::vector<PointLight*> m_pointLights;
	std::vector<SpotLight*>  m_spotLights;
public:
	void setShaderLightInfo(Shader* shader);
	iVec3 getLightNums();

	void addLight(Light* light);
	void addDirectLigth(DirectionLight* dlight);
	void addPointLight(PointLight* plight);
	void addSpotLight(SpotLight* splight);

	void removeLight(Light* light);
	void removeDirectLight(DirectionLight* dlight);
	void removePointLight(PointLight* plight);
	void removeSpotLight(SpotLight* splight);
};

END_NAMESPACE
#endif//__2022_04_01_LIGHT_MANAGER_H__