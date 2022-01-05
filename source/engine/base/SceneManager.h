#ifndef __2021_12_30_SCENE_MANAGER_H__
#define __2021_12_30_SCENE_MANAGER_H__

#include "common.h"

class Scene;
class RenderableComponent;

class SceneManager 
{
private:
	static SceneManager* s_instance;
public:
	static SceneManager* getInstance();
protected:
	friend class RenderableComponent;

	std::vector<RenderableComponent*> m_renderComps;

	void addRenderComp(RenderableComponent* com);
	void removeRenderComp(RenderableComponent* com);
	Scene* m_scene;
public:
	SceneManager();
	virtual ~SceneManager();

	Scene* getCurScene();
	void changeScene(Scene* scene);
	void render();
};
#endif//__2021_12_30_SCENE_MANAGER_H__