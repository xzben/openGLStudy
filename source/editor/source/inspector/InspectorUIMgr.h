#pragma once

#include "editor_common.h"
#include "core/tool/Singleton.h"
#include "view/EditorUIBase.h"
#include <unordered_map>

BEGIN_OGS_NAMESPACE
class Node;
class Asset;
class Scene;
END_OGS_NAMESPACE

BEGIN_EDITOR_NAMESPACE

typedef std::function<EditorUIBase* (const std::string& name, void* ob)> InspectorRenderFunc;

class InspectorUIMgr : public OGS::Object, public OGS::Singleton<InspectorUIMgr>
{
	DECLARE_RUNTIME_CLASS(InspectorUIMgr)
public:
	InspectorUIMgr();

	template<typename T>
	void registerUIRender(InspectorRenderFunc func)
	{
		registerUIRender(typeid(T).name(), func);
	}

	void registerUIRender(const std::string& name, InspectorRenderFunc func);
	EditorUIBase* getUIObject(const std::string& fieldtype, const std::string& name, void* data);

	template<typename T>
	EditorUIBase* getUIObject(T* object)
	{
		std::string name = typeid(T).name();
		
		return getUIObject(name, name, object);
	}
	EditorUIBase* getUIObject(OGS::Asset* asset);
private:
	std::unordered_map<std::string, InspectorRenderFunc> m_objRenders;
};
END_EDITOR_NAMESPACE