#include "AssetsFrame.h"
#include "core/filesystem/FileSystem.h"
#include "EditorApp.h"
#include "project/GameProject.h"
#include "view/widgets/EditorTreeNode.h"
BEGIN_EDITOR_NAMESPACE

static void buildAssetsTree(SharePtr<EditorTreeNode> rootnode, const std::string& path)
{
	std::vector<std::string> files;
	std::vector<std::string> directories;
	FileSystem::GetInstance()->getDirectoryContents(path, files, directories, false);
	for (auto dir : directories)
	{
		auto node = rootnode->CreateUI<EditorTreeNode>();
		node->leaf = false;
		node->setName(dir);
		buildAssetsTree(node, path + "/" + dir);
	}
	for (auto file : files)
	{
		auto node = rootnode->CreateUI<EditorTreeNode>();
		node->leaf = true;
		node->setDragable(true);
		node->setName(file);
	}
}
void AssetsFrame::handleInit()
{
	auto project = EditorApp::GetInstance()->GetProject();
	std::string rootpath = project->getAssetRoot();

	m_assets = CreateUI<EditorTreeNode>();
	m_assets->setName("Assets");
	buildAssetsTree(m_assets, rootpath);
}

END_EDITOR_NAMESPACE