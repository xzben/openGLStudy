#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "core/base/System.h"

#include <vector>

BEGIN_OGS_NAMESPACE

class GfxDevice;
class GameView;

class RenderSystem;

class Engine : public Object
{
	DECLARE_RUNTIME_CLASS(Engine)
public:
	Engine();
	virtual ~Engine();

	virtual bool init();
	virtual void update(float dt);

	virtual void preRender();
	virtual void render();
	virtual void draw();
	virtual void postRender();
protected:
	System* addSystem(System* sys);
protected:
	std::vector<AutoRef<System>> m_systems;
};

END_OGS_NAMESPACE