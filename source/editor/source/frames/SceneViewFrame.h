#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class SceneViewFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(SceneViewFrame)
public:
	SceneViewFrame(){}
	void handleInit() override;
};
END_EDITOR_NAMESPACE