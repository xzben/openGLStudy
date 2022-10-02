#pragma once
#include "reflex_define.h"
#include <string>
BEGIN_OGS_NAMESPACE

class ReflexClassBase
{
public:
	template<typename CLS>
	friend class ReflexClassMemberBase;
	friend class ReflexManager;
	friend class Serializer;

	ReflexClassBase(const char* name, ReflexClassBase* parent = nullptr) : m_parent(parent)
	{
		m_name = name;
	}

	virtual ~ReflexClassBase() = default;

	virtual bool Serialize(void* obj, JSON& json) = 0;
	virtual bool Deserialize(void* obj, const JSON& json) = 0;
	virtual void* NewInstance() = 0;
	const std::string& GetName() { return m_name; }
protected:
	std::string m_name;
	ReflexClassBase* m_parent = nullptr; //∏∏¿‡
};

END_OGS_NAMESPACE