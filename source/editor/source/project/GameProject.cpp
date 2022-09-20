#include "GameProject.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_CLASS(GameProject)

std::string GameProject::getProjectFilename()
{
	return m_path + "/" + m_name;
}

bool GameProject::loadFromFile()
{
	return ReflexManager::GetInstance()->Parse<GameProject>(this, getProjectFilename());
}

void GameProject::saveToFile()
{
	ReflexManager::GetInstance()->Serialize(this, getProjectFilename());
}

std::string GameProject::getAssetRoot()
{
	return m_path + "/" + "assets";
}

END_EDITOR_NAMESPACE