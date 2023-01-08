#pragma once
#include "editor_common.h"
#include "core/base/GameApp.h"
#include <tuple>
#include <string>
BEGIN_EDITOR_NAMESPACE

class HubWindow;
class GameProject;

class ProjectHub
{
public:
	ProjectHub();
	void init();
	std::tuple<bool, GameProject*> run();
protected:
	void render();
	void draw();
private:
	AutoRef<OGS::GameView> m_gameview;
	AutoRef<OGS::Gfx::Device> m_device;
	AutoRef<HubWindow> m_hubwindow;
	AutoRef<GameProject> m_openProject;
	bool		m_ready;
};

END_EDITOR_NAMESPACE

