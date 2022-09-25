#pragma once
#include "reflexClassFieldBase.h"

BEGIN_OGS_NAMESPACE
template<typename CLS, typename FieldType>
class ReflexClassGetSetField : public ReflexClassMemberBase<CLS>
{
public:
	using GetFunc = const FieldType& (CLS::*)()const;
	using SetFunc = void (CLS::*)(const FieldType&);

	ReflexClassGetSetField(ReflexClassBase* cls, const char* name, GetFunc getfunc, SetFunc setfunc)
		: ReflexClassMemberBase<CLS>(cls, name)
		, m_get(getfunc)
		, m_set(setfunc)
	{

	}

	virtual void GetObjectValue(CLS* obj, void* value) override
	{
		(*(FieldType*)value) = (obj->*m_get)();
	}

	virtual void SetObjectValue(CLS* obj, void* value) override
	{
		(obj->*m_set)(*(FieldType*)value);
	}

	virtual bool Serialize(CLS* obj, JSON& json) override
	{
		FieldType value = (obj->*m_get)();
		return FieldSerialize::Serialize(json[m_name], &value);
	}

	virtual bool Deserialize(CLS* obj, const JSON& json) override
	{
		if (!json.isMember(m_name))
		{
			ASSERT(false, "must have field [%s]", m_name.c_str());
			return false;
		}
		FieldType value;
		if (!FieldSerialize::Deserialize(json[m_name], &value))
		{
			return false;
		}
		(obj->*m_set)(value);

		return true;
	}
private:
	GetFunc m_get;
	SetFunc m_set;
};

END_OGS_NAMESPACE