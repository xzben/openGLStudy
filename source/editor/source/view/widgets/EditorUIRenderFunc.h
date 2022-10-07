#pragma once

#include "editor_common.h"
#include "view/EditorUIBase.h"
#include "view/UIContainor.h"
#include <functional>
BEGIN_EDITOR_NAMESPACE

class EditorUIRenderFunc : public EditorUIContainor
{
	DECLARE_RUNTIME_CLASS(EditorUIRenderFunc)
public:
	using RenderFunc = std::function<void(EditorUIRenderFunc*)>;
	virtual bool init(RenderFunc func);
	virtual bool onRender();
private:
	RenderFunc m_renderFunc;
};
END_EDITOR_NAMESPACE