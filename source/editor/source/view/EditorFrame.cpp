#include "EditorFrame.h"
#include "EditorApp.h"
#include "EditorWindow.h"
#include "event/EditorEventMgr.h"
BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorFrame)

EditorFrame::EditorFrame(const std::string& title)
	: m_title(title)
{
}

EditorFrame::~EditorFrame()
{

}

void EditorFrame::onChangeVisible(bool visible)
{
	EditorFrameEvent event = visible ? EditorFrameEvent::FRAME_OPEN : EditorFrameEvent::FRAME_CLOSE;
	EventData* pevent = new EventDataFrame(this->m_frameid, event);
	EditorEventMgr::getInstance()->emitEvent(EditorEvent::FRAME, pevent);
	SAFE_DELTE(pevent);
}

void EditorFrame::setDockspace(ImGuiID dockid)
{
	if(dockid > 0)
		ImGui::DockBuilderDockWindow(m_title.c_str(), dockid);
}

bool EditorFrame::onRender()
{	
	if(ImGui::Begin(m_title.c_str(), &m_isVisible, m_windowflag))
	{
		checkFrameSizeChange();
		renderImp();
		EditorUIContainor::onRender();
	}
	ImGui::End();
	return true;
}

void EditorFrame::checkFrameSizeChange()
{
	ImVec2 pos = ImGui::GetWindowPos();
	ImVec2 size = ImGui::GetWindowSize();
	float titleheight = ImGui::GetCurrentWindow()->TitleBarHeight();
	Rect newRect;
	newRect.x = pos.x;
	newRect.y = pos.y + titleheight;
	newRect.width = size.x;
	newRect.height = size.y - titleheight;
	bool change = false;
	if (newRect.x != m_windowRect.x, newRect.y != m_windowRect.y)
	{
		m_windowRect.x = newRect.x;
		m_windowRect.y = newRect.y;
		change = true;
	}

	if (newRect.width != m_windowRect.width || newRect.height != m_windowRect.height)
	{
		m_windowRect.width = newRect.width;
		m_windowRect.height = newRect.height;
		change = true;
	}

	if (change)
	{
		handleFrameSizeChange();
	}

}
void EditorFrame::handleFrameSizeChange()
{

}

END_EDITOR_NAMESPACE