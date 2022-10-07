#pragma once

#include "editor_common.h"
#include "view/UIContainor.h"

BEGIN_EDITOR_NAMESPACE
class TabItemView : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(TabItemView)
public:
	virtual bool init(const std::string& title);
	virtual bool onRender() override;
protected:
	std::string m_title;
};
END_EDITOR_NAMESPACE
