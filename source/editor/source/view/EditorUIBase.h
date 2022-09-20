#pragma once

#include "editor_common.h"

BEGIN_EDITOR_NAMESPACE

class EditorUIBase
{
	DECLARE_EDITOR_CLASS_BASE(EditorUIBase)
public:
	EditorUIBase() {};
	virtual ~EditorUIBase(){}

	virtual bool render();
	virtual void handleInit() {}
	virtual bool onRender() = 0;

	void setVisible(bool visible)
	{
		if (m_isVisible != visible)
		{
			m_isVisible = visible;
			m_lastVisibleStatus = visible;
			onChangeVisible(m_isVisible);
		}
	}

	bool isVisible() const{ return m_isVisible; }
	virtual void onChangeVisible(bool visible) {};

	bool isEnable() const { return m_enable; }
	void setEnable(bool enable) { m_enable = enable; }
	const ImVec2& getSize() const { return m_size; }
	void setSize(const ImVec2& size) { m_size = size; }
	void setParent(EditorUIBase* parent) { m_parent = parent; }
public:
	bool breakLine{ true };
protected:
	EditorUIBase* m_parent{ nullptr };
	bool m_isVisible{true};
	bool m_lastVisibleStatus{ true };
	bool m_enable{ true };
	ImVec2 m_size{0, 0};
};
END_EDITOR_NAMESPACE