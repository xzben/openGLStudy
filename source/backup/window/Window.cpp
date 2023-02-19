#include "window/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <functional>
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
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	app->handleWindowSizeChange((float)width, (float)height);
}

void Window::keypress_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	if (app->isFilterEvent()) return;

	app->handleKeyboardPress(key, scancode, action, mods);
}

void Window::mouse_callback(GLFWwindow* win, int button, int action, int mods)
{
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	if (app->isFilterEvent()) return;

	app->handleMouse(button, action, mods);
}

void Window::cursorpos_callback(GLFWwindow* win, double x, double y)
{
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	if (app->isFilterEvent()) return;

	app->handleCursorpos(x, y);
}

void Window::cursorenter_callback(GLFWwindow* win, int entered)
{
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	app->handleCursorenter(entered == GLFW_TRUE);
}

void Window::window_focuse_callback(GLFWwindow* win, int focuse)
{
	Window* app = (Window*)glfwGetWindowUserPointer(win);
	if (focuse == 0)
	{
		app->setFocuse(false);
	}
	else
	{
		app->setFocuse(true);
	}
}

bool Window::init()
{
	//��ʼ�� glfw
	if (!glfwInit()) {
		return false;
	}

	//ָ��opengl �汾 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//ָ��ʹ��core �ں�ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//������Ļÿ������ʹ��4������������ɫ���塣
	glfwWindowHint(GLFW_SAMPLES, 4);

#if CUR_PLAT == PLAT_MAC 
	//Mac OS X ϵͳ��Ҫ����ע�ͣ�������ǰ����
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//��������
	m_window = glfwCreateWindow((int)m_winSize.width, (int)m_winSize.height, m_name.c_str(), NULL, NULL);
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

	//���ô��ڴ�С�仯�ص�����Ҫ���ô��ڴ�С��
	glfwSetWindowUserPointer((GLFWwindow*)m_window, this);
	glfwSetWindowSizeCallback((GLFWwindow*)m_window, Window::resize_callback);

	glfwSetKeyCallback((GLFWwindow*)m_window, Window::keypress_callback);
	glfwSetMouseButtonCallback((GLFWwindow*)m_window, Window::mouse_callback);
	glfwSetCursorPosCallback((GLFWwindow*)m_window, Window::cursorpos_callback);
	glfwSetCursorEnterCallback((GLFWwindow*)m_window, Window::cursorenter_callback);
	glfwSetWindowFocusCallback((GLFWwindow*)m_window, Window::window_focuse_callback);

	return true;
}

void Window::setFocuse(bool focuse)
{
	m_isFocuse = focuse;
}

void Window::handleWindowSizeChange(float width, float height) {
	this->m_winSize.width = width;
	this->m_winSize.height = height;

	//0, 0 �������½�λ��
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	Application::getInstance()->setFrameSize(width, height);
}

void Window::handleKeyboardPress(int key, int scancode, int action, int mods)
{
	Application::getInstance()->dispatchKeyboard(key, action == GLFW_PRESS || action == GLFW_REPEAT);
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

	this->m_lastMouseX = (float)x;
	this->m_lastMouseY = (float)y;

	if (this->m_mouseClicked) {
		Application::getInstance()->dispatchTouch(TouchStatus::TOUCH_MOVE, this->m_lastMouseX, this->m_lastMouseY);
	}
}

void Window::handleCursorenter(bool enter)
{
	//CCLOG("handleCursorenter enter:%d\r\n", enter ? 1 : 0);
}


void Window::mainLoop()
{
	float lasttime = (float)glfwGetTime();
	while (!glfwWindowShouldClose((GLFWwindow*)m_window))
	{
		//�����¼��ռ�
		glfwPollEvents();

		//��ȡ��ǰʱ��
		float curtime = (float)glfwGetTime();
		float offset = curtime - lasttime;
		lasttime = curtime;
		
		Application::getInstance()->setLastTime(lasttime);

		//update�ƶ�ʱ�䣬���ﵽһ֡ʱ��ʱ��ᴥ����Ⱦ�����ֻ���Ⱦ����
		//���� ������������ʾ
		if (Application::getInstance()->shiftTime(offset))
		{
			//����ϵͳ update 
			Application::getInstance()->update();

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			//������Ȳ���
			glEnable(GL_DEPTH_TEST);

			//���ö��ز���
			glEnable(GL_MULTISAMPLE);
			
			// ���������������� ��ɫbuf �� ���buf
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
			//��ʼ����� ͼ����Ⱦ
			Application::getInstance()->render();

			//��������ȥ��Ļ��Ⱦ
			glfwSwapBuffers((GLFWwindow*)m_window);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		}
	}
	glfwTerminate();
}

END_NAMESPACE