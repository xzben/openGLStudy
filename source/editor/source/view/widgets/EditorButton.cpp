#include "EditorButton.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorButton)

bool EditorButton::onRender()
{
	if (ImGui::Button(m_text.c_str()))
	{
		onClick();
	}

	return true;
}

bool EditorButton::init(const std::string& text)
{
	if (!Super::init()) return false;

	setText(text);

	return true;
}
void EditorButton::onClick()
{
	ClickedEvent.emit();
}

END_EDITOR_NAMESPACE