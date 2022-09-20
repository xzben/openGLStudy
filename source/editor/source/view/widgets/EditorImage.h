#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorImage : public EditorUIBase
{
	DECLARE_EDITOR_CLASS(EditorImage)
public:
	void setPath(const std::string& path) { m_path = path; }
	const std::string& getPath() { return m_path; }
	virtual bool onRender() override;
protected:
	std::string m_path;
};

END_EDITOR_NAMESPACE