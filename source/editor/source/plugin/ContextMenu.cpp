#include "ContextMenu.h"

BEGIN_EDITOR_NAMESPACE

bool ContextMenu::render()
{
	//渲染不走render 走插件的 execute
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