#include "EditorApp.h"
#include "core/base/Engine.h"
#include "view/EditorWindow.h"
#include "core/view/GameView.h"
#include "event/EditorEventMgr.h"
#include "view/DefineId.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

EditorApp::EditorApp()
{
	m_editor_window = makeShare(new EditorWindow());
}

EditorApp::~EditorApp()
{
}

void EditorApp::initEvent()
{
	EditorEventMgr::GetInstance()->getNotifybyEvent(EditorEvent::MENU)->subscribe(this, &EditorApp::handleMenuEvent);
}

void EditorApp::handleMenuEvent(EventData* event)
{
	if (event->sourceId == IDMainMenu::FILE_EXIT)
	{
		exit();
	}
}

void EditorApp::unInitEvent()
{
	EditorEventMgr::GetInstance()->getNotifybyEvent(EditorEvent::MENU)->unsubscribe(this, &EditorApp::handleMenuEvent);
}

void EditorApp::onInit()
{
	initEvent();
	m_editor_window->init(m_gameView);
}

void EditorApp::onDestroy()
{
	unInitEvent();
	m_editor_window.release();
}

void EditorApp::onAppLauch()
{

}

void EditorApp::onAppExit()
{
	
}

void EditorApp::onPreRender()
{
	Super::onPreRender();
	m_editor_window->preRender();
}

void EditorApp::onRender()
{
	m_editor_window->render();
	Super::onRender();
}

void EditorApp::onPostRender()
{
	m_editor_window->postRender();
	Super::onPostRender();
}

void EditorApp::onDraw()
{
	m_editor_window->draw();
	Super::onDraw();
}

void EditorApp::onUpdate(float dt)
{
	Super::onUpdate(dt);
}


END_EDITOR_NAMESPACE