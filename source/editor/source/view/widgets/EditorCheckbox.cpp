#include "EditorCheckBox.h"


BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorCheckBox)

bool EditorCheckBox::onRender()
{
	bool preChecked = m_isChecked;
	ImGui::Checkbox(m_guid.c_str(), &m_isChecked);

	if (preChecked != m_isChecked)
	{
		EventCheck.emit(m_isChecked);
	}
	return true;
}

END_EDITOR_NAMESPACE