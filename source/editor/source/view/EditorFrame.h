#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"
#include "DefineId.h"
#include "imgui.h"
#include <string>
#include <vector>
#include <functional>
BEGIN_EDITOR_NAMESPACE

class EditorUIBase;
class EditorFrame;
class EditorWindow;

enum class LayoutType
{
	LEFT_RIGHT,
	TOP_DOWN,
};

class EditorFrame : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorFrame)
public:

	EditorFrame(const std::string& title);
	virtual ~EditorFrame();
	IDMainFrame getMainFrameId() { return m_frameid; }
	void setMainFrameId(IDMainFrame id) { m_frameid = id; }
	void setDockspaceId(MainDockSpace spaceid) { m_dockspaceId = spaceid; }
	void setDockFlag(ImGuiDockNodeFlags dockflag) { m_dockflag = dockflag; }
	void setWindowFlag(ImGuiWindowFlags windowflag) { m_windowflag = windowflag; }
	virtual bool render() override;
	void addChild(SharePtr<EditorUIBase>& child) { m_childrens.push_back(child); }
	const std::string& getTitle() { return m_title; }
	virtual void onChangeVisible(bool visible)override;
protected:
	std::string m_title;
	std::vector<SharePtr<EditorUIBase>> m_childrens;
	MainDockSpace m_dockspaceId{ MainDockSpace::EMPTY};
	WeakPtr<EditorWindow> m_window;
	ImGuiDockNodeFlags m_dockflag{0};
	ImGuiWindowFlags m_windowflag{0};
	IDMainFrame m_frameid{0};
};


END_EDITOR_NAMESPACE