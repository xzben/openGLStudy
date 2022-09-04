#include <iostream>
#include "EditorApp.h"

USING_OGS_NAMESPACE;
USING_EDITOR_NAMESPACE;

int main() {

	EditorApp::GetInstance()->init();
	EditorApp::GetInstance()->run();
	EditorApp::GetInstance()->destroy();

	return 0;
}