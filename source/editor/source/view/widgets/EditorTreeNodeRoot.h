#pragma once

#include "EditorTreeNode.h"

BEGIN_EDITOR_NAMESPACE

class EditorTreeNodeRoot : public EditorTreeNode
{
	DECLARE_RUNTIME_CLASS(EditorTreeNodeRoot)
public:
	EditorTreeNode* createTreeNode();
	Notify<EditorTreeNode*> EventChangeSelect;
	void forEachNode(EditorTreeNode* setNode, std::function<bool(EditorTreeNode*)> func);
	void openAll();
	void closeAll();
protected:
	virtual void handleInit() override;
	void handleSelectNode(EditorTreeNode* node);
protected:
	EditorTreeNode* m_curSelected{ nullptr };
};
END_EDITOR_NAMESPACE