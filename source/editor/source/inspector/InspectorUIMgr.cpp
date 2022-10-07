#include "InspectorUIMgr.h"
#include "view/widgets.h"
#include "core/base/Node.h"
#include "core/assets/items/Asset.h"
#include "inspector/InspectorUIRenderRegister.h"

BEGIN_EDITOR_NAMESPACE

IMPLEMENT_RUNTIME_CLASS(InspectorUIMgr)

InspectorUIMgr::InspectorUIMgr()
{
	registerCommonInspectorUI(this);
	registerNodeUIRender(this);
}

void InspectorUIMgr::registerUIRender(const std::string& name, InspectorRenderFunc func)
{
	m_objRenders[name] = func;
}

EditorUIBase* InspectorUIMgr::getUIObject(const std::string& fieldtype, const std::string& name, void* data)
{
	auto it = m_objRenders.find(fieldtype);
	if (it == m_objRenders.end()) return nullptr;
	return it->second(name, data);
}

EditorUIBase* InspectorUIMgr::getUIObject(OGS::Asset* asset)
{
	return EditorAreaBox::create();
}

END_EDITOR_NAMESPACE