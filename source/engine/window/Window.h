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
	static void keypress_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* win, int button, int action, int mods);
	static void cursorpos_callback(GLFWwindow* win, double x, double y);
	static void cursorenter_callback(GLFWwindow* win, int entered);
protected:

	float m_width;
	float m_heigth;
	std::string m_name;
	void* m_window;
	float x, y;
	int mouseStatus;


public:
	Window(std::string name, float width, float height);
	virtual ~Window();

	void mainLoop();
protected:
	bool init();
	void handleWindowSizeChange(float width, float height);
	void handleKeyboardPress(int key, int scancode, int action, int mods);
	void handleMouse(int button, int action, int mods);
	void handleCursorpos(double x, double y);
	void handleCursorenter(bool enter);
};

#endif//__2021_12_29_WINDOW_H__


