#include "TestScene.h"
#include "TestTriangle.h"
#include "TestRect.h"
#include "render/image/ImageComponent.h"
#include "base/Application.h"
#include "math/MathUtil.h"
#include "render/Color.h"
#include "game/test/BoxRender.h"
#include "event/Event.h"
#include "base/Application.h"
#include "event/EventDispatcher.h"
#include "math/Vec2.h"

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
	//this->addComponent(new ImageComponent("container.jpg"));

	this->addComponent(BoxRender::create());

	setColor(Color(1.f, 1.0f, 1.0f, 0.5f));


	Camera* cam = Application::getInstance()->getMainCamera();
	
	float step = 1;

	EventListener *touchListener = new EventListener(EventType::TOUCH, [=](Event* event){
		EventTouch* evt = (EventTouch*)event;
		fVec3 rot = cam->getRotation();

		if (evt->status == TouchStatus::TOUCH_MOVE)
		{
			fVec2 delta = evt->getDeltaPos();

			rot.x += delta.y / step;
			rot.y += delta.x / step;
			cam->setRotation(rot.x, rot.y, rot.z);
		}

		CCLOG(" touch %f %f %f\r\n", rot.x, rot.y, rot.z);
	});

	Application::getInstance()->getDispatcher()->addTouchListener(touchListener);
}

void TestScene::update(float dt)
{
	m_count += dt;

	float rot = m_count * 10;
	setRotation(rot, rot, rot);
}
