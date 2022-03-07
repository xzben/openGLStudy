#ifndef __2021_12_30_SCENE_MANAGER_H__
#define __2021_12_30_SCENE_MANAGER_H__

#include "common.h"
#include "render/RenderContainor.h"

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
	void changeScene(Scene* scene);
	virtual void render() override;
};
#endif//__2021_12_30_SCENE_MANAGER_H__