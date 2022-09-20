#include "EditorButton.h"

BEGIN_EDITOR_NAMESPACE

bool EditorButton::onRender()
{
	if (ImGui::Button(m_text.c_str()))
	{
		onClick();
	}

	return true;
}

void EditorButton::onClick()
{
	ClickedEvent.emit();
}

END_EDITOR_NAMESPACE