#pragma once

#include "editor_common.h"

BEGIN_EDITOR_NAMESPACE

class EditorUIBase
{
public:
	typedef EditorUIBase ThisType;
	EditorUIBase() {};
	virtual ~EditorUIBase(){}

	virtual bool render();

	void setVisible(bool visible)
	{
		if (m_isVisible != visible)
		{
			m_isVisible = visible;
			m_lastVisibleStatus = visible;
			onChangeVisible(m_isVisible);
		}
	}

	bool isVisible() { return m_isVisible; }
	virtual void onChangeVisible(bool visible) {};
protected:
	bool m_isVisible{true};
	bool m_lastVisibleStatus{ true };
};
END_EDITOR_NAMESPACE