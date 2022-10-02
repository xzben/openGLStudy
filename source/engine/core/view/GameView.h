#pragma once
#include "common.h"
#include "core/base/Object.h"
#include <functional>
#include <string>


struct GLFWwindow;

BEGIN_OGS_NAMESPACE

class GameView : public Object
{
	DECLARE_RUNTIME_CLASS(GameView)
public:
	typedef std::function<void()>                   onResetFunc;
	typedef std::function<void(int, int, int, int)> onKeyFunc;
	typedef std::function<void(unsigned int)>       onCharFunc;
	typedef std::function<void(int, unsigned int)>  onCharModsFunc;
	typedef std::function<void(int, int, int)>      onMouseButtonFunc;
	typedef std::function<void(double, double)>     onCursorPosFunc;
	typedef std::function<void(int)>                onCursorEnterFunc;
	typedef std::function<void(double, double)>     onScrollFunc;
	typedef std::function<void(int, const char**)>  onDropFunc;
	typedef std::function<void(int, int)>           onWindowSizeFunc;
	typedef std::function<void()>                   onWindowCloseFunc;
	GameView();
	virtual ~GameView();

	virtual void exit();
	virtual bool init(const WindowCreateInfo& info);
	virtual void destroy();
	virtual bool isShoudleClose()const;
	virtual void setTitle(const std::string& title);
	virtual GLFWwindow* GetWindow() const { return m_window; }
	virtual void getWindowSize(int& width, int& height) { width = m_width; height = m_height; }
	void setPosition(int x, int y);
	void show();
	void hide();
	void focus();
	void setfullscreen(bool fullscreen);
protected:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void charCallback(GLFWwindow* window, unsigned int codepoint);
	static void charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void dropCallback(GLFWwindow* window, int count, const char** paths);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	static void windowCloseCallback(GLFWwindow* window);

	void onReset();
	void onKey(int key, int scancode, int action, int mods);
	void onChar(unsigned int codepoint);
	void onCharMods(int codepoint, unsigned int mods);
	void onMouseButton(int button, int action, int mods);
	void onCursorPos(double xpos, double ypos);
	void onCursorEnter(int entered);
	void onScroll(double xoffset, double yoffset);
	void onDrop(int count, const char** paths);
	void onWindowSize(int width, int height);

	GLFWwindow* m_window{ nullptr };
	int m_width{ 0 };
	int m_height{ 0 };
	int m_posx{ 0 };
	int m_posy{ 0 };
	bool m_is_focus_mode{ false };
	bool m_fullscreen{ false };

	std::vector<onResetFunc>       m_onResetFunc;
	std::vector<onKeyFunc>         m_onKeyFunc;
	std::vector<onCharFunc>        m_onCharFunc;
	std::vector<onCharModsFunc>    m_onCharModsFunc;
	std::vector<onMouseButtonFunc> m_onMouseButtonFunc;
	std::vector<onCursorPosFunc>   m_onCursorPosFunc;
	std::vector<onCursorEnterFunc> m_onCursorEnterFunc;
	std::vector<onScrollFunc>      m_onScrollFunc;
	std::vector<onDropFunc>        m_onDropFunc;
	std::vector<onWindowSizeFunc>  m_onWindowSizeFunc;
	std::vector<onWindowCloseFunc> m_onWindowCloseFunc;
};

END_OGS_NAMESPACE