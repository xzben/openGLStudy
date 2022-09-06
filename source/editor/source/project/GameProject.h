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
	GameProject();

	void setPath(const std::string& path) { m_path = path; }

private:
	std::string m_path;
	std::string m_version;
};
END_EDITOR_NAMESPACE