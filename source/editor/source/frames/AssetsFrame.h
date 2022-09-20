#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE
class EditorTreeNode;

class AssetsFrame : public EditorFrame
{
	DECLARE_EDITOR_CLASS(AssetsFrame)
public:

	AssetsFrame() :EditorFrame("Assets") {}
	void handleInit() override;
private:
	SharePtr<EditorTreeNode> m_assets;
};
END_EDITOR_NAMESPACE