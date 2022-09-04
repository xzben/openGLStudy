#pragma once
#include "editor_common.h"
#include "core/base/GameApp.h"
#include "core/tool/Singleton.h"

USING_OGS_NAMESPACE;

BEGIN_OGS_NAMESPACE
class GameView;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE
class EditorWindow;
class EventData;

class EditorApp : public OGS::GameApp, public Singleton<EditorApp>
{
public:
	using ThisType = EditorApp;
	using Super = OGS::GameApp;

	EditorApp();
	virtual ~EditorApp();
	virtual void onInit() override;
	virtual void onDestroy() override;
	
	virtual void onAppLauch() override;
	virtual void onAppExit() override;

	virtual void onPreRender() override;
	virtual void onRender() override;
	virtual void onPostRender() override;
	virtual void onDraw() override;
	virtual void onUpdate(float dt) override;

	SharePtr<EditorWindow> getEditorWindow() { return m_editor_window; }
protected:
	void handleMenuEvent(EventData* event);
	void initEvent();
	void unInitEvent();
private:
	SharePtr<EditorWindow> m_editor_window;

};
END_EDITOR_NAMESPACE
