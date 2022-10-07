#pragma once
#include "reflexClassFieldBase.h"
#include "core/reflex/serializer/Serializer.h"
#include "core/ptr/SharePtr.h"
BEGIN_OGS_NAMESPACE

template<typename CLS, typename FieldType>
class ReflexClassSharePtrField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = SharePtr<FieldType> CLS::*;
	using Field = SharePtr<FieldType>;

	ReflexClassSharePtrField(ReflexClassBase* cls, const char* name, FieldPtr member, int flag)
		: ReflexClassMemberBase<CLS>(cls, name, flag)
		, m_member(member)
	{

	}

	virtual void* getFieldData(void* obj) override
	{
		CLS* clsobj = (CLS*)obj;
		Field ptr = clsobj->*m_member;

		return ptr.get();
	}

	virtual const char* getRawTypeName() override
	{
		return typeid(FieldType).name();
	}


	virtual void GetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		(*(Field*)value) = clsobj->*m_member;
	}

	virtual void SetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		clsobj->*m_member = *((Field*)value);
	}

	virtual bool Serialize(void* obj, JSON& json) override
	{
		CLS* clsobj = (CLS*)obj;
		Field value = (clsobj->*m_member);
		if (value == nullptr) return true;

		return FieldSerialize::Serialize(json[m_name], value);
	}

	virtual bool Deserialize(void* obj, const JSON& json) override
	{
		FieldType* value = nullptr;
		if (json.isMember(m_name))
		{
			const JSON& jsonvalue = json[m_name];
			if (jsonvalue.isObject())
			{
				value = (FieldType*)Serializer::Deserialize(jsonvalue);
			}
			else
			{
				value = new FieldType();
				if (!FieldSerialize::Deserialize(jsonvalue, value))
				{
					return false;
				}
			}
		}

		SetObjectValue(obj, makeShare<FieldType>(value));
		return true;
	}
private:
	FieldPtr m_member;
};

END_OGS_NAMESPACE