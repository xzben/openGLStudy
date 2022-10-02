#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

class EditorModalDialog : public EditorUIBase
{
	DECLARE_RUNTIME_CLASS(EditorModalDialog)
public:

	EditorModalDialog();
	virtual ~EditorModalDialog();

	virtual bool onRender() override;

};
END_EDITOR_NAMESPACE