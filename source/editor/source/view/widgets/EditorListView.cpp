#include "EditorListView.h"

BEGIN_EDITOR_NAMESPACE

bool EditorListView::render()
{
	if (!Super::render()) return false;

	ImGui::BeginChild("", m_size, true);
	for (auto item : m_items)
	{
		item->render();
	}
	ImGui::EndChild();

	return true;
}
END_EDITOR_NAMESPACE