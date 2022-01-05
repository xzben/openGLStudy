#include "window/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include "base/Application.h"

Window* Window::s_instance = nullptr;

Window* Window::getInstance() {
	CC_ASSET(s_instance != nullptr);
	return s_instance;
}

Window::Window(std::string name, float width, float height) 
	: m_name(name)
	, m_width(width)
	, m_heigth(height)
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
	m_window = glfwCreateWindow(m_width, m_heigth, m_name.c_str(), NULL, NULL);
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

	//指定窗口大小
	glViewport(0, 0, m_width, m_heigth);

	//设置窗口大小变化回调，主要重置窗口大小用
	glfwSetFramebufferSizeCallback((GLFWwindow*)m_window, Window::resize_callback);

	return true;
}

void Window::handleWindowSizeChange(float width, float height) {
	this->m_width = width;
	this->m_heigth = height;
	glViewport(0, 0, width, height);
}

void Window::mainLoop()
{
	float lasttime = glfwGetTime();
	while (!glfwWindowShouldClose((GLFWwindow*)m_window))
	{
		float curtime = glfwGetTime();
		float offset = curtime - lasttime;
		lasttime = curtime;
		
		Application::getInstance()->setLastTime(lasttime);

		if (Application::getInstance()->update(offset))
		{
			Application::getInstance()->render();
			glfwSwapBuffers((GLFWwindow*)m_window);
			glfwPollEvents();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		}
	}
	glfwTerminate();
}