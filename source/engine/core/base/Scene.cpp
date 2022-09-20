#include "Scene.h"
#include "Node.h"
#include "core/components/Camera.h"
#include "core/components/Transform.h"
BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Scene)

BEGIN_REFLEX_CLASS_FIELD(Scene)
REFLEX_FIELD(std::string, Scene::m_name)
END_REFLEX_CLASS_FIELD()

Scene* Scene::createDefaultScene()
{
	Scene* scene = Scene::create();

	Node* camera = Node::create();
	camera->createComponent<Transform>();
	camera->createComponent<Camera>();
	scene->addChild(camera);

	return scene;
}

Scene::Scene()
{

}
END_OGS_NAMESPACE