#ifndef __2021_12_29_WINDOW_H__
#define __2021_12_29_WINDOW_H__

#include "common.h"

class GLFWwindow;

class Window
{
private:
	static Window* s_instance;
public:
	static Window* getInstance();
	static void resize_callback(GLFWwindow* win, int width, int height);
	
protected:

	float m_width;
	float m_heigth;
	std::string m_name;
	void* m_window;
public:
	Window(std::string name, float width, float height);
	virtual ~Window();

	void mainLoop();
protected:
	bool init();
	void handleWindowSizeChange(float width, float height);
	void process_input();


};

#endif//__2021_12_29_WINDOW_H__


