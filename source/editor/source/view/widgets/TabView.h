#pragma once

#include "editor_common.h"
#include "view/UIContainor.h"

BEGIN_EDITOR_NAMESPACE
class TabItemView;

class TabView : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(TabView)
public:
	TabView() = default;
	virtual ~TabView() = default;
	virtual bool onRender() override;

	TabItemView* addTabItem(const std::string& name);
};
END_EDITOR_NAMESPACE
