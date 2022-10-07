#pragma once

#include "editor_common.h"
#include "plugin/IPlugin.h"
#include "view/UIContainor.h"
BEGIN_EDITOR_NAMESPACE

class ContextMenu : public IPlugin, public EditorUIContainor
{
public:
	virtual bool render() override;
	virtual void excute() override;

	void close();
};

END_EDITOR_NAMESPACE