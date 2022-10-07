#include "EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorUIBase)

EditorUIBase::EditorUIBase()
{
	m_guid = "##"+std::to_string((ptrsize)this);
}

bool EditorUIBase::render()
{
	if (m_lastVisibleStatus != m_isVisible)
	{
		m_lastVisibleStatus = m_isVisible;
		onChangeVisible(m_isVisible);
	}

	if (!m_isVisible)
		return false;

	if(m_size.x != 0 )
		ImGui::SetNextItemWidth(m_size.x);

	
	if (!onRender())
	{
		return false;
	}

	if (m_autoExecutePlugins)
		executePlugins();

	if (!breakLine)
		ImGui::SameLine();

	return true;
}

END_EDITOR_NAMESPACE