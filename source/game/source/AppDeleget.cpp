#include "AppDeleget.h"
#include "base/Scene.h"
#include "base/SceneManager.h"
#include "test/TestScene.h"
#include "utils/FileUtils.h"
#include "core/thread/TaskPool.h"
#include "core/thread/Task.h"
#include <iostream>

void AppDeleget::onAppLauchFinish()
{
	FileUtils::getInstance()->addSearchPath(DEFINE_XSTR(GAME_RESOURCE));
	FileUtils::getInstance()->addSearchPath(DEFINE_XSTR(BUILTIN_RES_DIR));

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

}