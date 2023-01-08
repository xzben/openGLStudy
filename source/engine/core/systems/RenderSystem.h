#pragma once

#include "define.h"
#include "core/ptr/WeakRef.h"
#include "core/ptr/AutoRef.h"
#include "core/base/System.h"
#include "core/math/Rect.h"
#include <vector>

BEGIN_OGS_GFX_NAMESPACE
class Device;
END_OGS_GFX_NAMESPACE
BEGIN_OGS_NAMESPACE

class CameraComponent;
class Renderable;
class Scene;

class RenderWindow;

class RenderSystem : public System
{
	DECLARE_RUNTIME_CLASS(RenderSystem)
public:
	friend class Engine;
	static RenderSystem* s_instance;
	static RenderSystem* getInstance();
public:
	RenderSystem();
	virtual void update(float dt) override;
	virtual void destroy() override;

	void updateEngineContentViewport(const Rect& viewport);
	void setRenderScene(Scene* scene);

	void addCamera(CameraComponent* camera);
	void removeCamera(CameraComponent* camera);

	void addRenderable(Renderable* obj);
	void removeRenderable(Renderable* obj);

	void addRenderWindow(RenderWindow* window);
	void removeRenderWindow(RenderWindow* window);

	RenderWindow* getDefaultRenderWindow() { return m_defaultRenderWindow.get(); }
	virtual void preRender();
	virtual void render();
	virtual void postRender();
	virtual void draw();
protected:
	void handleInit() override;
	WeakRef<Scene> m_curScene;
	AutoRef<RenderWindow> m_defaultRenderWindow;
	std::vector<CameraComponent*> m_cameras;
	std::vector<RenderWindow*>	  m_renderwindows;
	std::vector<Renderable*>	  m_renders;
	std::vector<Renderable*>	  m_uirenders;
	Gfx::Device* m_divice;
};
END_OGS_NAMESPACE