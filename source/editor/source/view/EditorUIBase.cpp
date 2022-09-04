#include "EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

bool EditorUIBase::render()
{
	if (m_lastVisibleStatus != m_isVisible)
	{
		m_lastVisibleStatus = m_isVisible;
		onChangeVisible(m_isVisible);
	}

	return m_isVisible;
}

END_EDITOR_NAMESPACE