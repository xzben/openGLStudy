#include "TestScene.h"
#include "TestTriangle.h"
#include "TestRect.h"
#include "render/image/ImageComponent.h"
#include "base/Application.h"
#include "math/MathUtil.h"
#include "render/Color.h"

USING_NAMESPACE;

TestScene::TestScene() 
{
	m_count = 0;
}

TestScene::~TestScene()
{
	
}

void TestScene::onLoad()
{
	this->addComponent(new ImageComponent("container.jpg"));
}

void TestScene::update(float dt)
{
	m_count += dt;
	//setRotationX(-45);
}
