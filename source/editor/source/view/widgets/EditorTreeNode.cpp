#include "EditorTreeNode.h"

BEGIN_EDITOR_NAMESPACE

void EditorTreeNode::onClick()
{
	
}

void EditorTreeNode::open()
{
	m_shouldOpen = true;
	m_shouldClose = false;
}

void EditorTreeNode::close()
{
	m_shouldOpen = false;
	m_shouldClose = true;
}

bool EditorTreeNode::onRender()
{
	bool preOpened = m_opened;

	if (m_shouldOpen)
	{
		ImGui::SetNextItemOpen(true);
		m_shouldOpen = false;
	}
	else if (m_shouldClose)
	{
		ImGui::SetNextItemOpen(false);
		m_shouldClose = false;
	}

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
	if (m_arrowClickOpen) flags |= ImGuiTreeNodeFlags_OpenOnArrow;
	if (selected)			flags |= ImGuiTreeNodeFlags_Selected;
	if (leaf)				flags |= ImGuiTreeNodeFlags_Leaf;

	bool isOpen = ImGui::TreeNodeEx(name.c_str(), flags);
	if (ImGui::IsItemClicked())
	{
		ClickedEvent.emit();

		if (ImGui::IsMouseDoubleClicked(0))
		{
			DoubleClickEvent.emit();
		}
	}

	if (m_dragable && ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
		ImGui::Text(name.c_str());
		ImGui::EndDragDropSource();
	}

	if (isOpen)
	{
		if (!preOpened)
			OpenEvent.emit();
		m_opened = true;
		EditorUIContainor::onRender();

		ImGui::TreePop();
	}
	else
	{
		if (preOpened)
		{
			ClosedEvent.emit();
		}

		m_opened = false;
	}

	return true;
}

END_EDITOR_NAMESPACE