#pragma once

#include "common.h"
#include "runtime.h"
#include "core/base/Object.h"
#include "core/math/Rect.h"

BEGIN_OGS_GFX_NAMESPACE
class Device;
END_OGS_GFX_NAMESPACE

BEGIN_OGS_NAMESPACE
class Engine;
class GameView;


class GameApp : public Object
{
	DECLARE_RUNTIME_CLASS(GameApp)
private:
	static GameApp* s_instance;
public:
	GameApp();
	virtual ~GameApp();
	static GameApp* getApp() { return s_instance; }
	virtual bool init(const WindowCreateInfo& windowinfo) final;
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
	AutoRef<GameView>& GetGameView() { return m_gameView; }
	OGS::Gfx::Device* getDevice() { return m_device.get(); }
protected:
	AutoRef<Engine> m_engine;
	float	m_fps = 1.0f/60;
	uint	m_frameCount = 0;
	AutoRef<GameView> m_gameView;
	AutoRef<OGS::Gfx::Device> m_device;
};
END_OGS_NAMESPACE