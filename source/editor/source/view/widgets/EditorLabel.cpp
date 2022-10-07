#include "EditorLabel.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorLabel)

bool EditorLabel::onRender()
{
	ImGui::PushStyleColor(ImGuiCol_Text, m_color);
	ImGui::Text(m_title.c_str());
	ImGui::PopStyleColor();

	return true;
}

END_EDITOR_NAMESPACE