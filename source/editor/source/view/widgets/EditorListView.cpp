#include "EditorListView.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorListView)

bool EditorListView::onRender()
{
	ImGui::BeginChild(m_guid.c_str(), m_size, true);
	for (auto item : m_items)
	{
		item->render();
	}
	ImGui::EndChild();

	return true;
}
END_EDITOR_NAMESPACE