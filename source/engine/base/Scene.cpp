#include "base/Scene.h"
#include "light/DirectionLight.h"
#include "render/SkyBox.h"
BEGIN_NAMESPACE

Scene::Scene() 
	: m_skybox(nullptr)
	, m_mainLight(nullptr)
	, m_mainCamera(nullptr)
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
	auto light = DirectionLight::create();

	this->addChild(light);

	return light;
}

void Scene::setSkybox(SkyBox* skybox) 
{ 
	m_skybox = skybox; 
	skybox->setOwner(this);
	SAFE_ADD_REF(m_skybox);
}

void Scene::render(RenderData* render)
{
	RenderContainor::render(render);
	if (this->m_skybox)
	{
		this->m_skybox->render(render);
	}
}
END_NAMESPACE