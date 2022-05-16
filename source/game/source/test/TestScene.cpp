#include "TestScene.h"
#include "TestTriangle.h"
#include "TestRect.h"
#include "render/image/ImageComponent.h"
#include "base/Application.h"
#include "math/MathUtil.h"
#include "render/Color.h"
#include "test/BoxRender.h"
#include "event/Event.h"
#include "base/Application.h"
#include "event/EventDispatcher.h"
#include "math/Vec2.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "Cube.h"
#include "render/SkyBox.h"
#include "Plane.h"

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
		CCLOG(" touch x:%f y:%f z:%f\r\n", rot.x, rot.y, rot.z);
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

	SkyBox* skybox = new SkyBox();
	std::string faces[6];
	faces[0] = "texture/skybox/right.jpg";
	faces[1] = "texture/skybox/left.jpg";
	faces[2] = "texture/skybox/top.jpg";
	faces[3] = "texture/skybox/bottom.jpg";
	faces[4] = "texture/skybox/front.jpg";
	faces[5] = "texture/skybox/back.jpg";
	skybox->init(faces);
	setSkybox(skybox);

	auto box = Node::create();
	box->setTag(1);

	box->addComponent(BoxRender::create());
	this->addChild(box);
	box->setPosition(-2, 0, 0);

	Light* poinglight = PointLight::create();
	this->addChild(poinglight);
	poinglight->setPosition(-1.f, 0.f, 0.f);

	auto cube = Cube::createColorMaterial();
	cube->setTag(2);
	this->addChild(cube);
	cube->setPosition(0, 0, 0);

	Light* poinglight1 = PointLight::create();
	this->addChild(poinglight1);
	poinglight1->setPosition(1.f, 0.f, 0.f);

	auto cube2 = Cube::createSampleMaterial();
	cube2->setTag(3);
	this->addChild(cube2);
	cube2->setPosition(2, 0, 0);

	auto plane = Plane::createColorMaterial();
	this->addChild(plane);
	plane->setPosition(0, -1, 0);

	Light* spotLight = SpotLight::create();
	spotLight->setPosition(0.f, 0.f, 2.f);
	this->addChild(spotLight);

	this->initEventListener();

	setColor(Color(1.f, 1.0f, 1.0f, 0.5f));

	this->getMainLight()->setPosition(3, 10, 3);
}

void TestScene::update(float dt)
{
	auto box = this->getChildByTag(1);
	auto cube = this->getChildByTag(2);
	auto cube2 = this->getChildByTag(3);

	Light* light = this->getMainLight();

	m_count += dt;
	float rot = m_count * 10;

	if (box)
	{
		box->setRotation(rot, rot, rot);
	}

	if (cube)
		cube->setRotation(rot, -rot, rot);

	if (cube2)
		cube2->setRotation(rot, rot, -rot);

	RGB lightClor;
	float step = m_count / 10;
	lightClor.r = sin(step*2.0f);
	lightClor.g = sin(step*0.7f);
	lightClor.b = sin(step*1.3f);

	RGB diffuseColor = lightClor * 0.5f;
	RGB ambientColor = diffuseColor * 0.2f;

	//light->setAmbientColor(ambientColor);
	//light->setDiffuseColor(diffuseColor);
}
