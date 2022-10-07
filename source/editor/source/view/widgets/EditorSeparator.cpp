#include "EditorSeparator.h"

BEGIN_EDITOR_NAMESPACE
IMPLEMENT_RUNTIME_CLASS(EditorSeparator)

bool EditorSeparator::onRender()
{
	ImGui::Separator();

	return true;
}

END_EDITOR_NAMESPACE