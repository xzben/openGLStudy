#ifndef __2022_01_04_TEST_SCENE_H__
#define __2022_01_04_TEST_SCENE_H__

#include "base/Scene.h"
#include "common.h"
USING_NAMESPACE;

class TestScene : public Scene
{
protected:
	float m_count;
	Node* m_box;

public:
	CREATE_FUNC(TestScene);

	 TestScene();
	 virtual ~TestScene();

	virtual void onLoad() override;
	void initEventListener();
	void update(float dt);

};
#endif//__2022_01_04_TEST_SCENE_H__