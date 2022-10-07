#include "EditorUIRenderFunc.h"

BEGIN_EDITOR_NAMESPACE
IMPLEMENT_RUNTIME_CLASS(EditorUIRenderFunc)

bool EditorUIRenderFunc::init(RenderFunc func)
{
	m_renderFunc = func;

	return true;
}

bool EditorUIRenderFunc::onRender()
{
	m_renderFunc(this);

	return true;
}

END_EDITOR_NAMESPACE