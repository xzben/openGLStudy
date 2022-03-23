#ifndef __2021_12_29_APPLICATION_H__
#define __2021_12_29_APPLICATION_H__

#include "common.h"
#include "math/math.h"
#include "base/Camera.h"

BEGIN_NAMESPACE

class EventDispatcher;

class Application
{
protected:
	static Application* s_instance;

protected:

	float m_offsetCount;
	float m_lasttime;
	float m_lastDt;
	float m_fps;

	fVec2 m_preTouchPos;
	ResolutionFit m_fitway;
	Size m_resolutionSize;
	Size m_frameSize;
	Size m_drawSize;

	EventDispatcher* m_dispatcher;
	Camera* m_mainCamera;
	friend class Window;
	void setFrameSize(const float& width, const float& height);
	void setFrameSize(const Size& frameSize);
	void updateDrawSize();
protected:
	fVec3 m_timer;

	friend class Shader;
	const fVec3& getShaderTimer() { return m_timer; }
public:
	Application();
	virtual ~Application();
	static Application* getInstance();

	Camera* getMainCamera();
	void setDesignResolution(float width, float height, ResolutionFit fit = ResolutionFit::AUTO_FIT);
	const Size& getFrameSize();
	const Size& getResolutionSize();

	void setFPS(int fps);
	float getFPF() { return this->m_fps;  }
	float getLastDt() { return this->m_lastDt;  }
	void setLastTime( float lastime) { this->m_lasttime = lastime; }
	float getLastTime() { return this->m_lasttime;  }

	//Æ«ÒÆÊ±²î
	bool shiftTime(float offsettime);
	bool update();
	void render();
	virtual void onAppLauchFinish() = 0;
	virtual void onAppPause() = 0;
	virtual void onAppResume() = 0;
	virtual void onAppExit() = 0;

	EventDispatcher* getDispatcher() { return m_dispatcher; }
	void dispatchKeyboard(int key, bool press);
	void dispatchTouch(TouchStatus status, float x, float y);
	void dispatchMouse(int key, bool press);
};

END_NAMESPACE

#endif//__2021_12_29_APPLICATION_H__

