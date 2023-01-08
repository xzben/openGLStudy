#include "Serializer.h"
#include "core/reflex/ReflexManager.h"

BEGIN_OGS_NAMESPACE

void* Serializer::Deserialize(const JSON& json)
{
	if (!json.isMember(CLASS_OBJ_KEY))
		return nullptr;

	const char* objname = json[CLASS_OBJ_KEY].asCString();
	ReflexClassBase* cls = ReflexManager::getInstance()->GetReflexClass(objname);
	if (cls == nullptr)
		return nullptr;

	void* obj = cls->NewInstance();

	ReflexClassBase* parent = cls;
	const JSON* pJson = &json;
	while (parent)
	{
		parent->Deserialize(obj, *pJson);
		parent = parent->m_parent;
		if (parent)
		{
			pJson = &(*pJson)[CLASS_SUPER_KEY];
		}
	}

	return obj;
}

END_OGS_NAMESPACE