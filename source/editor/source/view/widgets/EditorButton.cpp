#include "EditorButton.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorButton)

bool EditorButton::onRender()
{
	if (ImGui::Button(m_title.c_str()))
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