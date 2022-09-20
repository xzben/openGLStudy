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
	SharePtr<OGS::GameView> m_gameview;
	SharePtr<OGS::GfxDevice> m_device;
	SharePtr<HubWindow> m_hubwindow;

	GameProject* m_openProject{ nullptr };
	bool		m_ready;
};

END_EDITOR_NAMESPACE

