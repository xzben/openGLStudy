#include "ContextMenu.h"

BEGIN_EDITOR_NAMESPACE

bool ContextMenu::render()
{
	//��Ⱦ����render �߲���� execute
	return true;
}

void ContextMenu::excute()
{
	if (ImGui::BeginPopupContextItem())
	{
		EditorUIContainor::render();
		ImGui::EndPopup();
	}
}

void ContextMenu::close()
{
	ImGui::CloseCurrentPopup();
}

END_EDITOR_NAMESPACE