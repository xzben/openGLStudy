#pragma once

#include "core/reflex/reflex_define.h"
#include "core/reflex/reflexClass.h"

BEGIN_OGS_NAMESPACE

template<typename CLS>
class ReflexClassMemberBase
{
public:
	ReflexClassMemberBase(ReflexClassBase* cls, const char* name) :
		m_cls(cls)
	{
		m_name = "$" + cls->m_name + "$." + name;
	}

	virtual ~ReflexClassMemberBase() = default;

	virtual void GetObjectValue(CLS* obj, void* value) = 0;
	virtual void SetObjectValue(CLS* obj, void* value) = 0;

	virtual bool Serialize(CLS* obj, JSON& json) = 0;
	virtual bool Deserialize(CLS* obj, const JSON& json) = 0;

	const std::string& GetName() { return m_name; }
protected:
	std::string m_name;
	ReflexClassBase* m_cls;
};


template<typename CLS, typename FieldType>
class ReflexClassCommonField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = FieldType CLS::*;
	ReflexClassCommonField(ReflexClassBase* cls, const char* name, FieldPtr member)
		: ReflexClassMemberBase<CLS>(cls, name)
		, m_member(member)
	{

	}

	virtual void GetObjectValue(CLS* obj, void* value) override
	{
		(*(FieldType*)value) = obj->*m_member;
	}

	virtual void SetObjectValue(CLS* obj, void* value) override
	{
		obj->*m_member = (*(FieldType*)value);
	}

	virtual bool Serialize(CLS* obj, JSON& json) override
	{
		return FieldSerialize::Serialize(json[m_name], &(obj->*m_member));
	}

	virtual bool Deserialize(CLS* obj, const JSON& json) override
	{
		if (!json.isMember(m_name))
		{
			ASSERT(false, "must have field [%s]", m_name.c_str());
			return false;
		}
		return FieldSerialize::Deserialize(json[m_name], &(obj->*m_member));
	}
private:
	FieldPtr m_member;
};

END_OGS_NAMESPACE