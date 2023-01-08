#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class GameViewFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(GameViewFrame)
public:
	GameViewFrame(){}
protected:
	virtual void renderImp() override;
	void handleInit() override;
	void handleFrameSizeChange() override;
};
END_EDITOR_NAMESPACE