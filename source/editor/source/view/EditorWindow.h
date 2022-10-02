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

using EditorFrameCreator = std::function<EditorFrame*()>;
struct FrameConfig
{
	IDMainFrame id;
	MainDockSpace spaceid;
	const char* name;
	EditorFrameCreator creator;
};

class EditorWindow : public OGS::Object
{
	DECLARE_RUNTIME_CLASS(EditorWindow)
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
	virtual bool init(OGS::GameView* view);
	virtual void preRender();
	virtual void render();
	virtual void postRender();
	virtual void draw();
private:
	bool initUI();
	void renderMainDockSpace();
	void createFrameWindowSubMenu(int index, EditorFrame* frame);
	void setupMenuBar();
	void setupFrames();
	void addFrame(EditorFrame* frame, const FrameConfig& config);
	bool initContext();
	void handleFrameEvent(EventData* event);
	void EditorWindow::defaultLaytout(int dockspace_id);
protected:
	struct MainFrameInfo
	{
		AutoRef<EditorFrame> frame;
		FrameConfig config;
	};
	AutoRef<EditorMenuBar> m_menubar;
	WeakRef<EditorMenu> m_windowmenu;
	std::vector<MainFrameInfo> m_frames;
	WeakRef<OGS::GameView> m_gameview;
	std::unordered_map<MainDockSpace, ImGuiID> m_spaceId2GuiId;
	bool m_isInitDock{ true };
};

END_EDITOR_NAMESPACE