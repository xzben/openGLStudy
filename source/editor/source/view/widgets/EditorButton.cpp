#include "EditorButton.h"

BEGIN_EDITOR_NAMESPACE

bool EditorButton::render()
{
	if (!Super::render()) return false;

	if (ImGui::Button(m_text.c_str()))
	{
		onClick();
	}

	return true;
}

void EditorButton::onClick()
{

}

END_EDITOR_NAMESPACE