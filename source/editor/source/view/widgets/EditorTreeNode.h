#pragma once

#include "editor_common.h"
#include "core/base/Object.h"
#include "view/EditorUIBase.h"
#include "view/UIContainor.h"
#include "core/base/Notify.h"
USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class EditorTreeNode : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(EditorTreeNode)
public:
	void setName(const std::string& name) { this->name = name; }
	virtual bool onRender() override;
	void open();
	void close();
	void setCustomData(OGS::Object* customdata) { m_customData = customdata; }
	OGS::Object* getCustomData() { return m_customData.get(); }
public:
	std::string name;
	bool selected{ false };
	bool leaf{ false };
	bool doubleClickOpen{ true };

	Notify<EditorTreeNode*> ClickedEvent;
	Notify<EditorTreeNode*> DoubleClickEvent;
	Notify<EditorTreeNode*> OpenEvent;
	Notify<EditorTreeNode*> ClosedEvent;
	Notify<EditorTreeNode*> SelectEvent;
protected:
	AutoRef<OGS::Object> m_customData;
	bool m_arrowClickOpen{ true };
	bool m_shouldOpen{ false };
	bool m_shouldClose{ false };
	bool m_opened{ false };
};

END_EDITOR_NAMESPACE