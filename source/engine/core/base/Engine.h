#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "core/ptr/SharePtr.h"
#include "core/base/System.h"

#include <vector>

BEGIN_OGS_NAMESPACE

class GfxDevice;
class GameView;

class Engine
{
public:
	Engine(const SharePtr<GameView>& gameview);
	virtual ~Engine();

	virtual bool init();
	virtual void update(float dt);
	virtual void preRender();
	virtual void render();
	virtual void postRender();

	virtual void draw();
	virtual void swapFrameBuffer();
protected:
	std::vector<SharePtr<System>> m_systems;
	GfxDevice* m_device;
};

END_OGS_NAMESPACE