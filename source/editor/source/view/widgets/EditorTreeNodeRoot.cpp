#include "EditorTreeNodeRoot.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(EditorTreeNodeRoot);

void EditorTreeNodeRoot::forEachNode(EditorTreeNode* setNode, std::function<bool(EditorTreeNode*)> func)
{	
	if (func(setNode))
	{
		return;
	}

	auto childrens = setNode->getChildrens();
	for (auto child : childrens)
	{
		auto curnode = child->ToCast<EditorTreeNode>();
		if (curnode)
		{
			forEachNode(curnode, func);
		}
	}
}

EditorTreeNode* EditorTreeNodeRoot::createTreeNode()
{
	auto node = EditorTreeNode::create();
	node->SelectEvent += [this](EditorTreeNode* node) {
		this->handleSelectNode(node);
	};

	node->ClickedEvent += [this](EditorTreeNode* node) {
		this->ClickedEvent.emit(node);
	};

	node->DoubleClickEvent += [this](EditorTreeNode* node) {
		this->DoubleClickEvent.emit(node);
	};

	return node;
}

void EditorTreeNodeRoot::openAll()
{
	forEachNode(this, [this](EditorTreeNode* curnode)->bool {
		curnode->open();

		return false;
	});
}

void EditorTreeNodeRoot::closeAll()
{
	forEachNode(this, [this](EditorTreeNode* curnode)->bool {
		curnode->close();

		return false;
	});
}

void EditorTreeNodeRoot::handleSelectNode(EditorTreeNode* node)
{
	if (m_curSelected != node)
	{
		m_curSelected = node;
		forEachNode(this, [this, node](EditorTreeNode* curnode)->bool {
			curnode->selected = curnode == node;
			return false;
		});
		EventChangeSelect.emit(node);
	}	
}

void EditorTreeNodeRoot::handleInit()
{
	this->SelectEvent += [this](EditorTreeNode* node) {
		this->handleSelectNode(node);
	};
}

END_EDITOR_NAMESPACE