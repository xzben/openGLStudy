#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class GameViewFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(GameViewFrame)
public:
	GameViewFrame(){}
	void handleInit() override;
};
END_EDITOR_NAMESPACE