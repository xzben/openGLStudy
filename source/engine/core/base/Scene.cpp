#include "Scene.h"
#include "Node.h"
#include "Camera.h"
#include "core/components/Transform.h"
#include "core/components/CameraComponent.h"


BEGIN_OGS_NAMESPACE

IMPLEMENT_CLASS(Scene)

BEGIN_REFLEX_CLASS_FIELD(Scene)
END_REFLEX_CLASS_FIELD()


Scene* Scene::createDefaultScene()
{
	Scene* scene = Scene::create();

	Node* camera = Camera::createDefault3DCamera();
	scene->addChild(camera);

	return scene;
}

Scene::Scene()
{
	setName("Scene");
}

END_OGS_NAMESPACE