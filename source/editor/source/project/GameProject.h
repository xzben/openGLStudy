#pragma once

#include "editor_common.h"
#include "core/reflex/reflex.h"
#include "core/base/Notify.h"
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
	GameProject(const std::string& name) : m_name(name) {}
	virtual ~GameProject();
	void setPath(const std::string& path) { m_path = path; }
	const std::string& getPath() { return m_path; }
	void setName(const std::string& name) { m_name = name; }
	
	AutoRef<OGS::Asset> getOpenAsset();
	AutoRef<OGS::Asset> getActiveAsset() { return m_activeAsset; }
	AutoRef<OGS::Node>  getActiveNode() { return m_activeNode; }
	void setActiveAsset(OGS::Asset* asset);
	void setOpenAsset(OGS::Asset* asset);
	void setActiveNode(OGS::Node* node);
	std::string getAssetRoot();

	std::string getProjectFilename();
	bool loadFromFile();
	void saveToFile();
protected:
	void handleLoadFileDone();
public:
	OGS::Notify<OGS::Asset*> EventActiveAssetChange;
	OGS::Notify<OGS::Asset*> EventOpenAssetChange;
	OGS::Notify<OGS::Node*>  EventActiveNodeChange;
private:
	std::string m_name;
	std::string m_path;
	std::string m_version{ EDITOR_APP_VERSION };

	AutoRef<OGS::Asset> m_openAsset;
	AutoRef<OGS::Asset> m_activeAsset;
	AutoRef<OGS::Node>  m_activeNode;
};

END_EDITOR_NAMESPACE