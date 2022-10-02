#pragma once

#include "editor_common.h"
#include "core/base/Object.h"
BEGIN_EDITOR_NAMESPACE

class EditorUIContainor;

class EditorUIBase : public OGS::Object
{
	DECLARE_RUNTIME_CLASS(EditorUIBase)
public:
	EditorUIBase() {};
	virtual ~EditorUIBase(){}

	virtual bool render();
	virtual bool onRender() { return true; };

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
	void setParent(EditorUIContainor* parent) { m_parent = parent; }
public:
	bool breakLine{ true };
protected:
	EditorUIContainor* m_parent{ nullptr };
	bool m_isVisible{true};
	bool m_lastVisibleStatus{ true };
	bool m_enable{ true };
	ImVec2 m_size{0, 0};
};
END_EDITOR_NAMESPACE