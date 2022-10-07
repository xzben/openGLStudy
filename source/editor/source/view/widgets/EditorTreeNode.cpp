#include "EditorTreeNode.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorTreeNode)

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
	if(doubleClickOpen)  flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick; //Ë«»÷´ò¿ª
	if (m_arrowClickOpen) flags |= ImGuiTreeNodeFlags_OpenOnArrow;
	if (selected)			flags |= ImGuiTreeNodeFlags_Selected;
	if (leaf)				flags |= ImGuiTreeNodeFlags_Leaf;

	bool isOpen = ImGui::TreeNodeEx(name.c_str(), flags);
	if (ImGui::IsItemClicked())
	{
		if (!selected)
		{
			selected = true;
			SelectEvent.emit(this);
		}

		ClickedEvent.emit(this);

		
		if (ImGui::IsMouseDoubleClicked(0))
		{
			DoubleClickEvent.emit(this);
		}
	}

	if (isOpen)
	{
		if (!preOpened)
			OpenEvent.emit(this);
		m_opened = true;
		EditorUIContainor::onRender();

		ImGui::TreePop();
	}
	else
	{
		if (preOpened)
		{
			ClosedEvent.emit(this);
		}

		m_opened = false;
	}

	return true;
}

END_EDITOR_NAMESPACE