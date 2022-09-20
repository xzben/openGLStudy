#include "EditorLabel.h"

BEGIN_EDITOR_NAMESPACE

bool EditorLabel::onRender()
{
	ImGui::PushStyleColor(ImGuiCol_Text, m_color);
	ImGui::Text(m_text.c_str());
	ImGui::PopStyleVar();

	return true;
}

END_EDITOR_NAMESPACE