#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include "view/UIContainor.h"
#include "core/base/Notify.h"
USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class EditorTreeNode : public EditorUIBase, public EditorUIContainor
{
	DECLARE_EDITOR_CLASS(EditorTreeNode)
public:
	void setName(const std::string& name) { this->name = name; }
	virtual bool onRender() override;
	void setDragable(bool dragable) { m_dragable = dragable; }
	bool isDragable() { return m_dragable; }
	void open();
	void close();
	void setCustomData(SharePtr<void> customdata) { m_customData = customdata; }
	SharePtr<void> getCustomData() { return m_customData; }
protected:
	virtual void onClick();
public:
	std::string name;
	bool selected{ false };
	bool leaf{ false };

	Notify<> ClickedEvent;
	Notify<> DoubleClickEvent;
	Notify<> OpenEvent;
	Notify<> ClosedEvent;
protected:
	SharePtr<void> m_customData;
	bool m_arrowClickOpen{ false };
	bool m_shouldOpen{ false };
	bool m_shouldClose{ false };
	bool m_opened{ false };
	bool m_dragable{ false };
};

END_EDITOR_NAMESPACE