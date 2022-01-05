#include <iostream>
#include "window/Window.h"
#include "AppDeleget.h"


int main() {
	AppDeleget app;
	Window window("OpenGLStudy", 800, 600);
	app.onAppLauchFinish();
	window.mainLoop();
	app.onAppExit();
}