#pragma once

#include "editor_common.h"
#include "core/reflex/reflex.h"
#include <string>

BEGIN_OGS_NAMESPACE
class Node;
class Scene;
class AssetScene;
class AssetPrefab;
class Asset;

END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE

class GameProject : public OGS::Object
{
	DECLARE_CLASS(GameProject)
	DECLARE_REFLEX_CLASS_FIELD(GameProject);
public:
	GameProject() = default;
	GameProject(const std::string&& name) : m_name(name) {}
	virtual ~GameProject();
	void setPath(const std::string&& path) { m_path = path; }
	void setName(const std::string&& name) { m_name = name; }
	
	SharePtr<OGS::Asset> getEditorAsset() { return m_editorAsset; }
	void setEditorAsset(SharePtr<OGS::Asset> asset) { m_editorAsset = asset; }

	std::string getAssetRoot();

	std::string getProjectFilename();
	bool loadFromFile();
	void saveToFile();
protected:
	void handleLoadFileDone();
private:
	std::string m_name;
	std::string m_path;
	std::string m_version{ EDITOR_APP_VERSION };

	SharePtr<OGS::Asset> m_editorAsset;
};

END_EDITOR_NAMESPACE