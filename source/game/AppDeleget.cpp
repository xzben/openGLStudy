#include "AppDeleget.h"
#include "base/Scene.h"
#include "base/SceneManager.h"
#include "test/TestScene.h"
#include "utils/FileUtils.h"

void AppDeleget::onAppLauchFinish()
{
	FileUtils::getInstance()->addSearchPath("Resources/");
	FileUtils::getInstance()->addSearchPath("../Resources/");
	FileUtils::getInstance()->addSearchPath("../../Resources/");

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