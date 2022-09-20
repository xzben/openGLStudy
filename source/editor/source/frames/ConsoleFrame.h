#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class ConsoleFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(ConsoleFrame)
public:
	ConsoleFrame(){}
	void handleInit() override;

};
END_EDITOR_NAMESPACE