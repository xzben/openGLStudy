#pragma once

#include "editor_common.h"
#include "core/reflex/reflex.h"
#include <string>

USING_OGS_NAMESPACE;

BEGIN_EDITOR_NAMESPACE

class GameProject : public OGS::Object
{
	DECLARE_CLASS(GameProject)
public:
	GameProject() = default;
	GameProject(const std::string&& name) : m_name(name) {}
	void setPath(const std::string&& path) { m_path = path; }
	void setName(const std::string&& name) { m_name = name; }
	
	std::string getAssetRoot();

	std::string getProjectFilename();
	bool loadFromFile();
	void saveToFile();
private:
	std::string m_name;
	std::string m_path;
	std::string m_version;
};
END_EDITOR_NAMESPACE