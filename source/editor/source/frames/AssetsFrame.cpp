#include "AssetsFrame.h"
#include "core/filesystem/FileSystem.h"
#include "EditorApp.h"
#include "project/GameProject.h"
#include "view/widgets/EditorTreeNodeRoot.h"
#include "core/assets/AssetsMgr.h"
#include "core/assets/items/Asset.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(AssetsFrame)

static void buildAssetsTree(EditorTreeNodeRoot* rootnode, EditorTreeNode* curnodee, const std::string& path)
{
	std::vector<std::string> files;
	std::vector<std::string> directories;
	FileSystem::GetInstance()->getDirectoryContents(path, files, directories, false);
	for (auto dir : directories)
	{
		auto node = rootnode->createTreeNode();
		curnodee->addChild(node);
		node->leaf = false;
		node->setName(dir);
		buildAssetsTree(rootnode, node, path + "/" + dir);
	}

	for (auto file : files)
	{
		auto node = rootnode->createTreeNode();
		curnodee->addChild(node);
		OGS::Asset* asset = AssetsMgr::GetInstance()->getAsset(path+"/"+file);
		node->setCustomData(asset);
		node->leaf = true;
		node->setName(file);
	}
}

void AssetsFrame::handleInit()
{
	auto project = EditorApp::GetInstance()->GetProject();
	std::string rootpath = project->getAssetRoot();

	m_assets = CreateUI<EditorTreeNodeRoot>();
	m_assets->setName("Assets");

	m_assets->EventChangeSelect += [](EditorTreeNode* node) {
		if (node->getCustomData())
		{
			OGS::Asset* asset = node->getCustomData()->ToCast<OGS::Asset>();
			if (asset)
			{
				EditorApp::GetInstance()->GetProject()->setActiveAsset(asset);
			}
		}
	};

	m_assets->DoubleClickEvent += [](EditorTreeNode* node) {
		if (node->getCustomData())
		{
			OGS::Asset* asset = node->getCustomData()->ToCast<OGS::Asset>();
			if (asset)
			{
				EditorApp::GetInstance()->GetProject()->setOpenAsset(asset);
			}
		}
	};
	buildAssetsTree(m_assets.get(), m_assets.get(), rootpath);
}

END_EDITOR_NAMESPACE