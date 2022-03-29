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
	m_box = nullptr;
	m_count = 0;
}

TestScene::~TestScene()
{
	
}

void TestScene::initEventListener()
{
	Camera* cam = this->getMainCamera();

	float step = 1;

	EventListener* touchListener = new EventListener(EventType::TOUCH, [=](Event* event) {
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

	float mvStep = 0.1f;
	EventListener* keyboardListner = new EventListener(EventType::KEYBOARD, [=](Event* event) {
		EventKeyboard* evt = (EventKeyboard*)event;
		POSITION curPos = cam->getPosition();
		switch (evt->key)
		{
		case (int)Keyboard::KEY_W:
		{
			curPos.y += mvStep;
			break;
		}
		case (int)Keyboard::KEY_S:
		{
			curPos.y -= mvStep;
			break;
		}
		case (int)Keyboard::KEY_A:
		{
			curPos.x -= mvStep;
			break;
		}
		case (int)Keyboard::KEY_D:
		{
			curPos.x += mvStep;
			break;
		}
		}
		cam->setPosition(curPos);
		});

	Application::getInstance()->getDispatcher()->addTouchListener(touchListener);
	Application::getInstance()->getDispatcher()->addKeyboardListener(keyboardListner);
}
void TestScene::onLoad()
{
	//this->addComponent(new ImageComponent("container.jpg"));

	m_box = Node::create();
	m_box->addComponent(BoxRender::create());
	this->addChild(m_box);

	this->initEventListener();

	setColor(Color(1.f, 1.0f, 1.0f, 0.5f));

	Light* light = this->getMainLight();

	light->setLightColor(Color(1.0f, 1.0f, 1.0f));
	light->setPosition(1.2f, 1.0f, 2.0f);
}

void TestScene::update(float dt)
{
	if (m_box)
	{
		m_count += dt;

		float rot = m_count * 10;
		m_box->setRotation(rot, rot, rot);
	}

}
