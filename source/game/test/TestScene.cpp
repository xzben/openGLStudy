#include "TestScene.h"
#include "TestTriangle.h"
#include "TestRect.h"
#include "render/image/ImageComponent.h"

TestScene::TestScene() 
{

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