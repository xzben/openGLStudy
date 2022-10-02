#include "EditorTreeNodeRoot.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorTreeNodeRoot);

static void updateTreeNodeSelectStatus(EditorTreeNode* setNode, EditorTreeNode* selectednode)
{
	setNode->selected = setNode == selectednode;
	
	auto childrens = setNode->getChildrens();
	for (auto child : childrens)
	{
		auto curnode = child->ToCast<EditorTreeNode>();
		if (curnode)
		{
			updateTreeNodeSelectStatus(curnode, selectednode);
		}
	}
}

EditorTreeNode* EditorTreeNodeRoot::createTreeNode()
{
	auto node = EditorTreeNode::create();
	node->SelectEvent += [this](EditorTreeNode* node) {
		this->handleSelectNode(node);
	};
	return node;
}

void EditorTreeNodeRoot::handleSelectNode(EditorTreeNode* node)
{
	m_curSelected = node;
	updateTreeNodeSelectStatus(this, node);
}

void EditorTreeNodeRoot::handleInit()
{
	this->SelectEvent += [this](EditorTreeNode* node) {
		this->handleSelectNode(node);
	};
}

END_EDITOR_NAMESPACE