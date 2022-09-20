#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class NodeTreeFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(NodeTreeFrame)
public:
	NodeTreeFrame(){}
	void handleInit() override;
};
END_EDITOR_NAMESPACE