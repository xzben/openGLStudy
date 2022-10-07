#pragma once

#include "editor_common.h"
#include "view/EditorTitleUIBase.h"
#include <core/base/Notify.h>
BEGIN_EDITOR_NAMESPACE

class EditorButton : public EditorTitleUIBase
{
	DECLARE_RUNTIME_CLASS(EditorButton)
public:
	EditorButton() = default;
	virtual bool onRender() override;
private:
	virtual void onClick();
public:
	OGS::Notify<> ClickedEvent;

};
END_EDITOR_NAMESPACE