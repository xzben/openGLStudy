#include "window/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "base/Application.h"

BEGIN_NAMESPACE

Window* Window::s_instance = nullptr;

Window* Window::getInstance() {
	CC_ASSERT(s_instance != nullptr);
	return s_instance;
}

Window::Window(std::string name, float width, float height) 
	: m_name(name)
	, m_winSize(width, height)
{
	s_instance = this;
	this->init();
}

Window::~Window() {
	s_instance = nullptr;
}

void Window::resize_callback(GLFWwindow* win, int width, int height)
{
	Window::getInstance()->handleWindowSizeChange(width, height);
}

void Window::keypress_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	Window::getInstance()->handleKeyboardPress(key, scancode, action, mods);
}

void Window::mouse_callback(GLFWwindow* win, int button, int action, int mods)
{
	Window::getInstance()->handleMouse(button, action, mods);
}

void Window::cursorpos_callback(GLFWwindow* win, double x, double y)
{
	Window::getInstance()->handleCursorpos(x, y);
}

void Window::cursorenter_callback(GLFWwindow* win, int entered)
{
	Window::getInstance()->handleCursorenter(entered == GLFW_TRUE);
}

bool Window::init()
{
	//初始化 glfw
	glfwInit();

	//指定opengl 版本 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//指定使用core 内核模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if CUR_PLAT == PLAT_MAC 
	//Mac OS X 系统需要开启注释，开启向前兼容
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建窗口
	m_window = glfwCreateWindow(m_winSize.width, m_winSize.height, m_name.c_str(), NULL, NULL);
	if (m_window == NULL) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent((GLFWwindow*)m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	this->handleWindowSizeChange(this->m_winSize.width, this->m_winSize.height);

	//设置窗口大小变化回调，主要重置窗口大小用
	glfwSetFramebufferSizeCallback((GLFWwindow*)m_window, Window::resize_callback);
	glfwSetKeyCallback((GLFWwindow*)m_window, Window::keypress_callback);
	glfwSetMouseButtonCallback((GLFWwindow*)m_window, Window::mouse_callback);
	glfwSetCursorPosCallback((GLFWwindow*)m_window, Window::cursorpos_callback);
	glfwSetCursorEnterCallback((GLFWwindow*)m_window, Window::cursorenter_callback);

	return true;
}

void Window::handleWindowSizeChange(float width, float height) {
	this->m_winSize.width = width;
	this->m_winSize.height = height;

	//0, 0 代表左下角位置
	glViewport(0, 0, width, height);

	Application::getInstance()->setFrameSize(width, height);
}

void Window::handleKeyboardPress(int key, int scancode, int action, int mods)
{
	Application::getInstance()->dispatchKeyboard(key, action == GLFW_PRESS);
}

void Window::handleMouse(int button, int action, int mods)
{
	//CCLOG("mouse button:%d action:%d mods:%d\r\n", button, action, mods);
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_1:
	{
		this->m_mouseClicked = action == GLFW_PRESS;
		Application::getInstance()->dispatchTouch(this->m_mouseClicked ? TouchStatus::TOUCH_BEGAN : TouchStatus::TOUCH_END, this->m_lastMouseX, this->m_lastMouseY);
		break;
	}
	}

	Application::getInstance()->dispatchMouse(button, action == GLFW_PRESS);
}

void Window::handleCursorpos(double x, double y)
{
	//CCLOG("handleCursorpos x:%f y:%f\r\n", x, y);

	this->m_lastMouseX = x;
	this->m_lastMouseY = y;

	if (this->m_mouseClicked) {
		Application::getInstance()->dispatchTouch(TouchStatus::TOUCH_MOVE, x, y);
	}
}

void Window::handleCursorenter(bool enter)
{
	//CCLOG("handleCursorenter enter:%d\r\n", enter ? 1 : 0);
}

void Window::mainLoop()
{
	float lasttime = glfwGetTime();
	while (!glfwWindowShouldClose((GLFWwindow*)m_window))
	{
		//获取当前时间
		float curtime = glfwGetTime();
		float offset = curtime - lasttime;
		lasttime = curtime;
		
		Application::getInstance()->setLastTime(lasttime);

		//update推动时间，当达到一帧时间时则会触发渲染流程手机渲染命令
		//并且 交换缓冲区显示
		if (Application::getInstance()->shiftTime(offset))
		{
			Application::getInstance()->update();

			glDepthMask(true);
			glClearColor(0, 0, 0, 1);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDepthMask(false);
			Application::getInstance()->render();

			//交换缓冲去屏幕渲染
			glfwSwapBuffers((GLFWwindow*)m_window);
			//触发事件收集
			glfwPollEvents();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		}
	}
	glfwTerminate();
}

END_NAMESPACE