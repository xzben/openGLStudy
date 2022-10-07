#include "EditorAreaBox.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorAreaBox)


bool EditorAreaBox::onRender()
{
	ImGui::BeginChild(m_guid.c_str(), m_size, true, ImGuiWindowFlags_HorizontalScrollbar);
	Super::onRender();
	ImGui::EndChild();

	return true;
}

END_EDITOR_NAMESPACE