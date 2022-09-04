#pragma once

#include "editor_common.h"
#include "EditorUIBase.h"

BEGIN_EDITOR_NAMESPACE

class EditorModalDialog : public EditorUIBase
{
public:
	typedef ThisType Super;
	typedef EditorModalDialog ThisType;

	EditorModalDialog();
	virtual ~EditorModalDialog();

	virtual bool render() override;

};
END_EDITOR_NAMESPACE