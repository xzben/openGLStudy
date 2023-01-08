#include <iostream>
#include "EditorApp.h"
#include "hub/ProjectHub.h"
#include "project/GameProject.h"

USING_OGS_NAMESPACE;
USING_EDITOR_NAMESPACE;

int main() 
{
	EditorApp::getInstance();
	bool ready = true;
	AutoRef<GameProject> project = new GameProject("project");
	project->setPath(MACRO_XSTR(ENGINE_PROJECT_PATH));
	project->loadFromFile();
	//ProjectHub hub;
	//hub.init();
	//std::tie(ready, project) =  hub.run();

	if (ready && project)
	{
		EditorApp::getInstance()->init(project);
		EditorApp::getInstance()->run();
		EditorApp::getInstance()->destroy();
	}

	return 0;
}