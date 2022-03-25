#include "base/Scene.h"

BEGIN_NAMESPACE

Scene::Scene() 
{

}

Scene::~Scene()
{

}

Camera* Scene::getMainCamera()
{
	if (m_mainCamera == nullptr) {
		m_mainCamera = createMainCamera();
	}

	return m_mainCamera;
}

Camera* Scene::createMainCamera()
{
	auto cam = Camera::createDefault(true);
	
	this->addChild(cam);

	return cam;
}

Light* Scene::getMainLight()
{
	if(m_mainLight == nullptr)
	{
		m_mainLight = createMainLight();
	}

	return m_mainLight;
}

Light* Scene::createMainLight()
{
	auto light = new Light();

	this->addChild(light);

	return light;
}

END_NAMESPACE