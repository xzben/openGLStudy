#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"


BEGIN_OGS_NAMESPACE
class Node;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE

class EditorTreeNodeRoot;

class NodeTreeFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(NodeTreeFrame)
public:
	NodeTreeFrame(){}
protected:
	void updateShowAsset();
	void handleInit() override;

protected:
	AutoRef<EditorTreeNodeRoot> m_treenode;
};
END_EDITOR_NAMESPACE