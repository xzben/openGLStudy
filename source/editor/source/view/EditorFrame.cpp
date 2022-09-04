#include "EditorFrame.h"
#include "EditorApp.h"
#include "EditorWindow.h"
#include "event/EditorEventMgr.h"
BEGIN_EDITOR_NAMESPACE

EditorFrame::EditorFrame(const std::string& title)
	: m_title(title)
{
	m_window = EditorApp::GetInstance()->getEditorWindow();
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

bool EditorFrame::render()
{
	if (!Super::render())
		return false;

	ImGuiID nodeid;
	if (m_dockspaceId != 0 && (nodeid = m_window->getDockspaceId(m_dockspaceId)) > 0)
	{
		ImGui::DockBuilderDockWindow(m_title.c_str(), nodeid);
	}
	
	if(ImGui::Begin(m_title.c_str(), &m_isVisible))
	{
		for (auto it : m_childrens)
		{
			it->render();
		}
	}
	ImGui::End();

	return true;
}

END_EDITOR_NAMESPACE