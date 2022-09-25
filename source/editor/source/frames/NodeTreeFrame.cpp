#include "NodeTreeFrame.h"
#include "EditorApp.h"
#include "project/GameProject.h"
#include "view/widgets/EditorTreeNode.h"
#include "core/base/Node.h"
#include "core/base/Scene.h"
#include "core/assets/items/Asset.h"
#include "core/assets/items/AssetPrefab.h"
#include "core/assets/items/AssetScene.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

static void updateTreeNode(SharePtr<EditorTreeNode> treenode, Node* node)
{
	if (node == nullptr) return;

	treenode->setName(node->getName());
	auto childs = node->getChildrens();
	treenode->leaf = childs.size() <= 0;

	for (auto ch : childs)
	{
		auto chtreenode = treenode->CreateUI<EditorTreeNode>();
		updateTreeNode(chtreenode, ch);
	}
}

void NodeTreeFrame::handleInit()
{
	SharePtr<Asset> asset = EditorApp::GetInstance()->GetProject()->getEditorAsset();
	m_treenode = CreateUI<EditorTreeNode>();
	Node* showNode = nullptr;

	if (asset->IsKindOf<AssetPrefab>())
	{
		showNode = asset->ToCast<AssetPrefab>()->getNode();
	}
	else if(asset->IsKindOf<AssetScene>())
	{
		showNode = asset->ToCast<AssetScene>()->getScene();
	}
	updateTreeNode(m_treenode, showNode);
}

END_EDITOR_NAMESPACE