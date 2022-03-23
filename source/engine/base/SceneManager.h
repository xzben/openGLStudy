#ifndef __2021_12_30_SCENE_MANAGER_H__
#define __2021_12_30_SCENE_MANAGER_H__

#include "common.h"
#include "render/RenderContainor.h"

BEGIN_NAMESPACE

class Scene;
class RenderableComponent;

class SceneManager : public RenderContainor
{
private:
	static SceneManager* s_instance;
public:
	static SceneManager* getInstance();
protected:
	Scene* m_scene;
public:
	SceneManager();
	virtual ~SceneManager();

	Scene* getCurScene();
	void update(float dt);
	void changeScene(Scene* scene);
	void render();
};

END_NAMESPACE

#endif//__2021_12_30_SCENE_MANAGER_H__