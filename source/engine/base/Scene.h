#ifndef __2021_12_30_SCENE_H__
#define __2021_12_30_SCENE_H__

#include "common.h"
#include "base/Node.h"
#include "render/RenderContainor.h"
#include "math/math.h"

class Scene : public Node, public RenderContainor
{
protected:
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
};
#endif//__2021_12_30_SCENE_H__