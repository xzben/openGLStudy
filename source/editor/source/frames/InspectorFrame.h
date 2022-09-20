#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE

class InspectorFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(InspectorFrame)
public:
	InspectorFrame(){}
	void handleInit() override;
};
END_EDITOR_NAMESPACE