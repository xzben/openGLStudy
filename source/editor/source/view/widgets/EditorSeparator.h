#pragma once
#include "editor_common.h"
#include "view/UIContainor.h"
BEGIN_EDITOR_NAMESPACE

class EditorSeparator : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorSeparator)
public:

protected:
	virtual bool onRender() override;
};

END_EDITOR_NAMESPACE