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
#include "Cube.h"

USING_NAMESPACE;

TestScene::TestScene() 
{
	m_count = 0;
}

TestScene::~TestScene()
{
	
}

void TestScene::initEventListener()
{
	Node* cam = this->getMainCamera();

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

	auto box = Node::create();
	box->setTag(1);

	box->addComponent(BoxRender::create());
	this->addChild(box);
	box->setPosition(-2, 0, 0);
	auto cube = Cube::create();
	cube->setTag(2);

	this->addChild(cube);
	cube->setPosition(2, 0, 0);

	this->initEventListener();

	setColor(Color(1.f, 1.0f, 1.0f, 0.5f));

	Light* light = this->getMainLight();

	light->setAmbientColor(RGB(0.2f, 0.2f, 0.2f));
	light->setDiffuseColor(RGB(0.5f, 0.5f, 0.5f));
	light->setSpecularColor(RGB(1.0f, 1.0f, 1.0f));
	light->setSpecularStrength(1.0f);
	light->setAmbientStrength(1.0f);
	light->setDiffuseStrength(1.0f);
	light->setPosition(3, 10, 3);
}

void TestScene::update(float dt)
{
	auto box = this->getChildByTag(1);
	auto cube = this->getChildByTag(2);
	Light* light = this->getMainLight();

	m_count += dt;
	float rot = m_count * 10;

	if (box)
	{
		box->setRotation(rot, rot, rot);
	}

	if (cube)
		cube->setRotation(rot, rot, rot);

	RGB lightClor;
	lightClor.r = sin(m_count*2.0f);
	lightClor.g = sin(m_count * 0.7f);
	lightClor.b = sin(m_count * 1.3f);

	RGB diffuseColor = lightClor * 0.5f;
	RGB ambientColor = diffuseColor * 0.2f;

	light->setAmbientColor(ambientColor);
	light->setDiffuseColor(diffuseColor);
}
