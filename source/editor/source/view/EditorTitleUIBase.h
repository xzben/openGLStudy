#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class EditorUIContainor;

class EditorTitleUIBase : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorTitleUIBase)
public:
	virtual bool init(const std::string& title);
	virtual bool onRender() { return true; };
	void setTitle(const std::string& title) { m_title = title; }
	const std::string& getTitle() { return m_title; }
protected:
	std::string	m_title{ "" };
};
END_EDITOR_NAMESPACE