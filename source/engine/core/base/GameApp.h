#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE
class Engine;
class GameView;
class GfxDevice;

class GameApp
{
public:
	GameApp();
	virtual ~GameApp();

	static GameApp* s_instance;
	static GameApp* GetApp() { return s_instance; }
	virtual bool init() final;
	virtual void destroy();
	virtual void update(float dt) final;
	virtual void render()final;
	virtual void draw()final;
	virtual void run() final;
	
	virtual void exit();
	virtual bool isShoudleClose();
	virtual void onAppLauch() {};
	virtual void onAppExit() {};

	virtual void onInit() {};
	virtual void onDestroy() {};
	virtual void onPreRender();
	virtual void onRender();
	virtual void onPostRender();
	virtual void onUpdate(float dt);
	virtual void onDraw();
	
	
	void setFps(int fps) { ASSERT(fps > 0, "framecount must > 0");  m_fps = 1.0f / fps; }
	uint getFrameCount() { return m_frameCount; }
	SharePtr<GameView>& GetGameView() { return m_gameView; }
protected:
	SharePtr<Engine> m_engine;
	float	m_fps = 1.0f/60;
	uint	m_frameCount = 0;
	SharePtr<GameView> m_gameView;
	SharePtr<GfxDevice> m_device;
};
END_OGS_NAMESPACE