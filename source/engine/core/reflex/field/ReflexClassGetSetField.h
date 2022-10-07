#pragma once
#include "reflexClassFieldBase.h"

BEGIN_OGS_NAMESPACE
template<typename CLS, typename FieldType>
class ReflexClassGetSetField : public ReflexClassMemberBase<CLS>
{
public:
	using GetFunc = const FieldType& (CLS::*)()const;
	using SetFunc = void (CLS::*)(const FieldType&);

	ReflexClassGetSetField(ReflexClassBase* cls, const char* name, GetFunc getfunc, SetFunc setfunc, int flag)
		: ReflexClassMemberBase<CLS>(cls, name, flag)
		, m_get(getfunc)
		, m_set(setfunc)
	{
		m_flags |= (int)ReflexConfig::NO_Edit;
	}

	virtual const char* getRawTypeName() override
	{
		return typeid(FieldType).name();
	}

	virtual void* getFieldData(void* obj) override
	{
		ASSERT(false, "get set can't field data");
		return nullptr;
	}

	virtual void GetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		(*(FieldType*)value) = (clsobj->*m_get)();
	}

	virtual void SetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		(clsobj->*m_set)(*(FieldType*)value);
	}

	virtual bool Serialize(void* obj, JSON& json) override
	{
		CLS* clsobj = (CLS*)obj;
		FieldType value = (clsobj->*m_get)();
		return FieldSerialize::Serialize(json[m_name], &value);
	}

	virtual bool Deserialize(void* obj, const JSON& json) override
	{
		CLS* clsobj = (CLS*)obj;
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
		(clsobj->*m_set)(value);

		return true;
	}
private:
	GetFunc m_get;
	SetFunc m_set;
};

END_OGS_NAMESPACE