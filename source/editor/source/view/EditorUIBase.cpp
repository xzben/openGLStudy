#include "EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

bool EditorUIBase::render()
{
	if (m_lastVisibleStatus != m_isVisible)
	{
		m_lastVisibleStatus = m_isVisible;
		onChangeVisible(m_isVisible);
	}

	if (!m_isVisible)
		return false;

	if (!onRender())
	{
		return false;
	}

	if (!breakLine)
		ImGui::SameLine();

	return true;
}

END_EDITOR_NAMESPACE