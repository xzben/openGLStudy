#include "EditorCheckBox.h"


BEGIN_EDITOR_NAMESPACE

bool EditorCheckBox::render()
{
	if (!Super::render()) return false;

	ImGui::Checkbox(m_text.c_str(), &m_isChecked);

	return true;
}

END_EDITOR_NAMESPACE