#include "TestScene.h"
#include "TestTriangle.h"
#include "TestRect.h"
#include "render/image/ImageComponent.h"
#include "base/Application.h"
#include "math/MathUtil.h"

TestScene::TestScene() 
{
	m_count = 0;
}

TestScene::~TestScene()
{
	
}

void TestScene::onLoad()
{
	this->addComponent(new TestTriangle());

	this->addComponent(new TestRect());

	this->addComponent(new ImageComponent("wall.jpg"));
}

void TestScene::update(float dt)
{
	m_count += dt;
	Quaternion q;
	Quaternion::createFromAxisAngle(fVec3(0, 0, -1), m_count, &q);
	this->m_matModel = MathUtil::rotation(q);
}
