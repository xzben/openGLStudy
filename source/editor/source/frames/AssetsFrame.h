#pragma once

#include "editor_common.h"
#include "view/EditorFrame.h"

BEGIN_EDITOR_NAMESPACE
class EditorTreeNodeRoot;

class AssetsFrame : public EditorFrame
{
	DECLARE_RUNTIME_CLASS(AssetsFrame)
public:

	AssetsFrame(){}
	void handleInit() override;
private:
	WeakRef<EditorTreeNodeRoot> m_assets;
};

END_EDITOR_NAMESPACE