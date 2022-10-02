#include "NodeTreeFrame.h"
#include "EditorApp.h"
#include "project/GameProject.h"
#include "view/widgets/EditorTreeNodeRoot.h"
#include "core/base/Node.h"
#include "core/base/Scene.h"
#include "core/assets/items/Asset.h"
#include "core/assets/items/AssetPrefab.h"
#include "core/assets/items/AssetScene.h"

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(NodeTreeFrame)

static void updateTreeNode(EditorTreeNodeRoot* rootnode, EditorTreeNode* treenode, Node* node)
{
	if (node == nullptr) return;

	treenode->setCustomData(node);
	treenode->setName(node->getName());
	auto childs = node->getChildrens();
	treenode->leaf = childs.size() <= 0;

	for (auto ch : childs)
	{
		auto chtreenode = rootnode->createTreeNode();
		treenode->addChild(chtreenode);
		updateTreeNode(rootnode, chtreenode, ch);
	}
}

void NodeTreeFrame::updateShowAsset()
{
	auto project = EditorApp::GetInstance()->GetProject();
	WeakRef<Asset> asset = project->getActiveAsset();
	if (!asset) return;
	Node* showNode = nullptr;

	if (asset->IsKindOf<AssetPrefab>())
	{
		showNode = asset->ToCast<AssetPrefab>()->getNode();
	}
	else if (asset->IsKindOf<AssetScene>())
	{
		showNode = asset->ToCast<AssetScene>()->getScene();
	}
	if (showNode)
	{
		updateTreeNode(m_treenode.get(), m_treenode.get(), showNode);
	}
}

void NodeTreeFrame::handleInit()
{
	auto project = EditorApp::GetInstance()->GetProject();
	project->EventActiveAssetChange += [this](OGS::Asset* asset) {
		this->updateShowAsset();
	};
	m_treenode = CreateUI<EditorTreeNodeRoot>();
	m_treenode->setName("Null");
	m_treenode->EventChangeSelect += [](EditorTreeNode* treenode) {
		auto node = treenode->getCustomData()->ToCast<OGS::Node>();
		EditorApp::GetInstance()->GetProject()->setActiveNode(node);
	};
	updateShowAsset();
}

END_EDITOR_NAMESPACE