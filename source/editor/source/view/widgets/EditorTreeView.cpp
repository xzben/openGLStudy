#include "EditorTreeView.h"

BEGIN_EDITOR_NAMESPACE

void EditorTreeNode::onClick()
{
	
}

bool EditorTreeNode::render()
{
	if (!Super::render()) return false;

	bool isOpen = ImGui::TreeNodeEx(m_text.c_str(), ImGuiTreeNodeFlags_Selected);
	if (ImGui::IsItemClicked())
	{
		onClick();
	}
	if (m_dragable && ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
		ImGui::Text(m_text.c_str());
		ImGui::EndDragDropSource();
	}

	if (isOpen)
	{
		for (auto ch : m_childs)
		{
			ch->render();
		}

		ImGui::TreePop();
	}

	return true;
}

END_EDITOR_NAMESPACE