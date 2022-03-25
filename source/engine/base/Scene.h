#ifndef __2021_12_30_SCENE_H__
#define __2021_12_30_SCENE_H__

#include "common.h"
#include "base/Node.h"
#include "render/RenderContainor.h"
#include "math/math.h"
#include "base/Camera.h"
#include "light/Light.h"

BEGIN_NAMESPACE

class Scene : public Node, public RenderContainor
{
protected:
	Camera* m_mainCamera;
	Light* m_mainLight;

	Size m_size;
	void setSize(const Size& size) {
		this->m_size = size;
	}

	const Size& getSize() {
		return this->m_size;
	}

public:
	CREATE_FUNC(Scene);
	friend class SceneManager;
	Scene();
	virtual ~Scene();

	Camera* getMainCamera();
	Light* getMainLight();

	virtual Camera* createMainCamera();
	virtual Light* createMainLight();
};

END_NAMESPACE

#endif//__2021_12_30_SCENE_H__