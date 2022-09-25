#include "GameProject.h"
#include "core/base/Node.h"
#include "core/base/Scene.h"
#include "core/reflex/reflex.h"
#include "core/assets/items/AssetPrefab.h"
#include "core/reflex/serializer/Serializer.h"
#include "core/assets/items/AssetScene.h"
#include "core/base/Scene.h"
USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_CLASS(GameProject)

BEGIN_REFLEX_CLASS_FIELD(GameProject)
REFLEX_FIELD(std::string, m_version)
END_REFLEX_CLASS_FIELD()



END_EDITOR_NAMESPACE

BEGIN_EDITOR_NAMESPACE

GameProject::~GameProject()
{

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
	SharePtr<AssetScene> asset = makeShare<AssetScene>();
	asset->setScene(Scene::createDefaultScene());
	m_editorAsset = asset;
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