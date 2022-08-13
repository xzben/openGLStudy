#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "ReflexItem.h"
#include <unordered_map>
BEGIN_OGS_NAMESPACE

class ReflexManager : public Singleton<ReflexManager>
{
public:
	ReflexManager() = default;

	template<typename CLS>
	void Serialize(CLS* obj, JSON& json)
	{
		ReflexClassBase* reflex = CLS::GetREFLEX();
		reflex->Serialize(obj, json);
	}

	Object* Deserialize(const JSON& json)
	{

	}
};
END_OGS_NAMESPACE