#include "EditorCheckBox.h"


BEGIN_EDITOR_NAMESPACE

bool EditorCheckBox::onRender()
{
	ImGui::Checkbox(m_text.c_str(), &m_isChecked);
	return true;
}

END_EDITOR_NAMESPACE