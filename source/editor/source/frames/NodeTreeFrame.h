#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"


BEGIN_OGS_NAMESPACE
class Node;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE

class EditorTreeNode;

class NodeTreeFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(NodeTreeFrame)
public:
	NodeTreeFrame(){}
	void handleInit() override;

protected:
	SharePtr<EditorTreeNode> m_treenode;
};
END_EDITOR_NAMESPACE