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
	EditorEventMgr::GetInstance()->emitEvent(EditorEvent::FRAME, pevent);
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
		EditorUIContainor::onRender();
	}
	ImGui::End();

	return true;
}

END_EDITOR_NAMESPACE