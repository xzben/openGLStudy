#include "GameProject.h"
#include "core/base/Node.h"
#include "core/base/Scene.h"
#include "core/reflex/reflex.h"
#include "core/assets/items/AssetPrefab.h"
#include "core/reflex/serializer/Serializer.h"
#include "core/assets/items/AssetScene.h"
#include "core/filesystem/FileSystem.h"
#include "core/base/Scene.h"
USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(GameProject)
IMPLEMENT_REFLEX_CLASS_BASE(GameProject)

BEGIN_REFLEX_CLASS_FIELD(GameProject)
REFLEX_FIELD(std::string, m_version)
END_REFLEX_CLASS_FIELD()



END_EDITOR_NAMESPACE

BEGIN_EDITOR_NAMESPACE

GameProject::~GameProject()
{

}

void GameProject::setActiveAsset(OGS::Asset* asset)
{
	if (m_activeAsset == asset) return;
	m_activeAsset = asset;
	EventActiveAssetChange.emit(m_activeAsset.get());
}

void GameProject::setOpenAsset(OGS::Asset* asset)
{
	if (m_openAsset = asset) return;
	m_openAsset = asset;
	EventOpenAssetChange.emit(m_openAsset.get());
}

void GameProject::setActiveNode(OGS::Node* node)
{
	if (m_activeNode == node) return;
	m_activeNode = node;
	EventActiveNodeChange.emit(m_activeNode.get());
}

std::string GameProject::getProjectFilename()
{
	return m_path + "/" + m_name;
}

bool GameProject::loadFromFile()
{
	bool ok = Serializer::Parse<GameProject>(this, getProjectFilename());

	handleLoadFileDone();

	return ok;
}

void GameProject::handleLoadFileDone()
{

}

AutoRef<OGS::Asset> GameProject::getOpenAsset()
{
	if (m_openAsset == nullptr)
	{
		AutoRef<AssetScene> asset = new AssetScene();
		asset->setScene(Scene::createDefaultScene());
		m_openAsset = asset;
	}

	return m_openAsset;
}

void GameProject::saveToFile()
{
	Serializer::Serialize(this, getProjectFilename());
}

std::string GameProject::getAssetRoot()
{
	return m_path + "/" + "assets";
}

END_EDITOR_NAMESPACE