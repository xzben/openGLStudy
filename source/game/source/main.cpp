#include <iostream>
#include "window/Window.h"
#include "AppDeleget.h"


int main() {
	AppDeleget app;
	Window window("OpenGLStudy", 1280, 720);
	app.setGLWin(&window);
	app.run();
}