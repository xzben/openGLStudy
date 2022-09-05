#pragma once
#include "editor_common.h"
#include <vector>
#include <unordered_map>

BEGIN_OGS_NAMESPACE
class GameView;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE
class EditorFrame;
class EditorMenuBar;
class EditorMenu;
class EventData;

class EditorWindow
{
	DECLARE_EDITOR_CLASS_BASE(EditorWindow)
public:
	EditorWindow();
	virtual ~EditorWindow();

	void showFrame(EditorFrame* frame);
	void closeFrame(EditorFrame* frame);
	ImGuiID getDockspaceId(MainDockSpace spaceid);
protected:
	friend class EditorApp;
	void initEvent();
	void uninitEvent();
	virtual bool init(SharePtr<OGS::GameView>& view);
	virtual void preRender();
	virtual void render();
	virtual void postRender();
	virtual void draw();
private:
	bool initUI();
	void renderMainDockSpace();
	void createFrameWindowSubMenu(int index, SharePtr<EditorFrame>& frame);
	void setupMenuBar();
	void setupFrames();
	void addFrame(SharePtr<EditorFrame>& frame);
	bool  initContext();
	void handleFrameEvent(EventData* event);
	void EditorWindow::defaultLaytout(int dockspace_id);
protected:
	SharePtr<EditorMenuBar> m_menubar;
	WeakPtr<EditorMenu> m_windowmenu;
	std::vector<SharePtr<EditorFrame>> m_frames;
	WeakPtr<OGS::GameView> m_gameview;
	std::unordered_map<MainDockSpace, ImGuiID> m_spaceId2GuiId;
	bool m_isInitDock{ true };
};

END_EDITOR_NAMESPACE