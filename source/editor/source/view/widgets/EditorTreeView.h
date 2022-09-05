#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorTreeNode : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorTreeNode)
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() const { return m_text; }
	virtual bool render() override;
	void setDragable(bool dragable) { m_dragable = dragable; }
	bool isDragable() { return m_dragable; }
protected:
	virtual void onClick();
protected:
	std::string m_text;
	bool m_dragable{ false };
	std::vector<SharePtr<EditorTreeNode>> m_childs;
};

class EditorTreeView : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorTreeView)
public:

protected:
	std::vector<SharePtr<EditorUIBase>> m_nodes;
	std::string m_text;
};
END_EDITOR_NAMESPACE