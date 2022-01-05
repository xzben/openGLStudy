#include "AppDeleget.h"
#include "base/Scene.h"
#include "base/SceneManager.h"
#include "test/TestScene.h"

void AppDeleget::onAppLauchFinish()
{
	Scene* scene = TestScene::create();
	SceneManager::getInstance()->changeScene(scene);
}

void AppDeleget::onAppPause()
{

}

void AppDeleget::onAppResume()
{

}

void AppDeleget::onAppExit()
{
	Scene* scene = SceneManager::getInstance()->getCurScene();
	delete scene;
}