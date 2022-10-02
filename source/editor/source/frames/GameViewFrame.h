#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class GameViewFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(GameViewFrame)
public:
	GameViewFrame(){}
	void handleInit() override;
};
END_EDITOR_NAMESPACE