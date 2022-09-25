#include <iostream>
#include "EditorApp.h"
#include "hub/ProjectHub.h"
#include "project/GameProject.h"

USING_OGS_NAMESPACE;
USING_EDITOR_NAMESPACE;

#define MACRO_XSTR(s) MACRO_STR(s)
#define MACRO_STR(s) #s

int main() 
{

	bool ready = true;
	SharePtr<GameProject> project = makeShare(new GameProject("project"));
	project->setPath(MACRO_XSTR(ENGINE_PROJECT_PATH));
	project->loadFromFile();
	//ProjectHub hub;
	//hub.init();
	//std::tie(ready, project) =  hub.run();

	if (ready && project)
	{
		EditorApp::GetInstance()->init(project);
		EditorApp::GetInstance()->run();
		EditorApp::GetInstance()->destroy();
	}

	return 0;
}