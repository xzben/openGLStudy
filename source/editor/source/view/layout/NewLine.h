#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
BEGIN_EDITOR_NAMESPACE

class NewLine : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(NewLine)
protected:
	virtual bool onRender() override;
};
END_EDITOR_NAMESPACE