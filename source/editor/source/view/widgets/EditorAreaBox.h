#pragma once
#include "editor_common.h"
#include "view/UIContainor.h"
BEGIN_EDITOR_NAMESPACE

class EditorAreaBox : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(EditorAreaBox)
public:
	virtual bool onRender() override;
};

END_EDITOR_NAMESPACE