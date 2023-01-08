#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"
#include "DefineId.h"
#include "UIContainor.h"
#include "imgui.h"
#include "core/math/Rect.h"
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

class EditorFrame : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(EditorFrame)
public:
	EditorFrame() = default;
	EditorFrame(const std::string& title);
	virtual ~EditorFrame();
	IDMainFrame getMainFrameId() { return m_frameid; }
	void setMainFrameId(IDMainFrame id) { m_frameid = id; }
	void setDockFlag(ImGuiDockNodeFlags dockflag) { m_dockflag = dockflag; }
	void setWindowFlag(ImGuiWindowFlags windowflag) { m_windowflag = windowflag; }
	void setDockspace(ImGuiID dockid);
	virtual void renderImp() {}
	virtual bool onRender() override;

	const std::string& getTitle() { return m_title; }
	void setTitle(const std::string& title) { m_title = title; }
protected:
	virtual void onChangeVisible(bool visible)override;
	void checkFrameSizeChange();
	virtual void handleFrameSizeChange();
protected:
	std::string m_title{""};
	ImGuiDockNodeFlags m_dockflag{0};
	ImGuiWindowFlags m_windowflag{0};
	IDMainFrame m_frameid{0};
	OGS::Rect   m_windowRect{0,0,0,0};
};


END_EDITOR_NAMESPACE