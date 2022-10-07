#pragma once

#include "editor_common.h"
#include "core/base/Object.h"
#include "plugin/Pluginable.h"
BEGIN_EDITOR_NAMESPACE

class EditorUIContainor;

class EditorUIBase : public OGS::Object, public Pluginable
{
	DECLARE_RUNTIME_CLASS(EditorUIBase)
public:
	EditorUIBase();
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
	const std::string& getGuiD() { return m_guid; }
	bool isEnable() const { return m_enable; }
	void setEnable(bool enable) { m_enable = enable; }
	const ImVec2& getSize() const { return m_size; }
	void setSize(const ImVec2& size) { m_size = size; }
	void setWidth(float width) { m_size.x = width; }
	void setHeight(float height) { m_size.y = height; }
	void setSize(float width, float height) { m_size.x = width; m_size.y = height; }
	void setParent(EditorUIContainor* parent) { m_parent = parent; }
	void Sameline() { breakLine = false; }
	void Destry() { m_dirtyRemove = true; }
	bool isDirtyRemove() { return m_dirtyRemove; }
public:
	bool breakLine{ true };
protected:
	bool m_dirtyRemove{ false };
	std::string m_guid;
	EditorUIContainor* m_parent{ nullptr };
	bool m_isVisible{true};
	bool m_lastVisibleStatus{ true };
	bool m_enable{ true };
	ImVec2 m_size{0, 0};
	bool m_autoExecutePlugins{ true };
};
END_EDITOR_NAMESPACE