#include "GameView.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

BEGIN_OGS_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GameView)

// window event callbacks
void GameView::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onKey(key, scancode, action, mods);
	}
}

void GameView::charCallback(GLFWwindow* window, unsigned int codepoint)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onChar(codepoint);
	}
}

void GameView::charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onCharMods(codepoint, mods);
	}
}

void GameView::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onMouseButton(button, action, mods);
	}
}

void GameView::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onCursorPos(xpos, ypos);
	}
}

void GameView::cursorEnterCallback(GLFWwindow* window, int entered)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onCursorEnter(entered);
	}
}

void GameView::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onScroll(xoffset, yoffset);
	}
}

void GameView::dropCallback(GLFWwindow* window, int count, const char** paths)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->onDrop(count, paths);
	}
}

void GameView::windowSizeCallback(GLFWwindow* window, int width, int height)
{
	GameView* app = (GameView*)glfwGetWindowUserPointer(window);
	if (app)
	{
		app->m_width = width;
		app->m_height = height;
	}
}

void GameView::windowCloseCallback(GLFWwindow* window) 
{ 
	glfwSetWindowShouldClose(window, true); 
}

GameView::GameView()
{

}
GameView::~GameView()
{
}

bool GameView::init(const WindowCreateInfo& info)
{
	glfwWindowHint(GLFW_MAXIMIZED, info.maximized);

	m_width = info.width;
	m_height = info.height;
	m_posx = 0;
	m_posy = 0;
	GLFWwindow* window = glfwCreateWindow(info.width, info.height, info.title, info.is_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return false;
	}
	m_window = window;

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		CCLOG_ERROR("Failed to initialize GLAD");
		return false;
	}

	glfwSwapInterval(1); // Enable vsync

	 // Setup input callbacks
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCharCallback(window, charCallback);
	glfwSetCharModsCallback(window, charModsCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetDropCallback(window, dropCallback);
	glfwSetWindowSizeCallback(window, windowSizeCallback);
	glfwSetWindowCloseCallback(window, windowCloseCallback);

	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
	return true;
}

void GameView::destroy()
{
	glfwDestroyWindow((GLFWwindow*)m_window);
	glfwTerminate();
}

bool GameView::isShoudleClose()const
{
	return glfwWindowShouldClose((GLFWwindow*)m_window);
}

void GameView::setTitle(const std::string& title)
{
	glfwSetWindowTitle((GLFWwindow*)m_window, title.c_str());
}

void GameView::setPosition(int x, int y)
{
	m_posx = x;
	m_posy = y;
	glfwSetWindowPos(m_window, x, y);
}

void GameView::show()
{
	glfwShowWindow(m_window);
}

void GameView::hide()
{
	glfwHideWindow(m_window);
}
void GameView::focus()
{
	glfwFocusWindow(m_window);
}
void GameView::setfullscreen(bool fullscreen)
{
	m_fullscreen = fullscreen;
	glfwSetWindowMonitor
	(
		m_window,
		fullscreen ? glfwGetPrimaryMonitor() : nullptr,
		m_posx,
		m_posy,
		m_width,
		m_height,
		-1
	);
}

void GameView::exit()
{
	glfwSetWindowShouldClose((GLFWwindow*)m_window, true);
}

void GameView::onReset()
{
	for (auto& func : m_onResetFunc)
		func();
}
void GameView::onKey(int key, int scancode, int action, int mods)
{
	for (auto& func : m_onKeyFunc)
		func(key, scancode, action, mods);
}

void GameView::onChar(unsigned int codepoint)
{
	for (auto& func : m_onCharFunc)
		func(codepoint);
}
void GameView::onCharMods(int codepoint, unsigned int mods)
{
	for (auto& func : m_onCharModsFunc)
		func(codepoint, mods);
}
void GameView::onMouseButton(int button, int action, int mods)
{
	for (auto& func : m_onMouseButtonFunc)
		func(button, action, mods);
}
void GameView::onCursorPos(double xpos, double ypos)
{
	for (auto& func : m_onCursorPosFunc)
		func(xpos, ypos);
}
void GameView::onCursorEnter(int entered)
{
	for (auto& func : m_onCursorEnterFunc)
		func(entered);
}
void GameView::onScroll(double xoffset, double yoffset)
{
	for (auto& func : m_onScrollFunc)
		func(xoffset, yoffset);
}
void GameView::onDrop(int count, const char** paths)
{
	for (auto& func : m_onDropFunc)
		func(count, paths);
}
void GameView::onWindowSize(int width, int height)
{
	for (auto& func : m_onWindowSizeFunc)
		func(width, height);
}

END_OGS_NAMESPACE