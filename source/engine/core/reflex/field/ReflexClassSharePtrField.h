#pragma once
#include "reflexClassFieldBase.h"
#include "core/reflex/serializer/Serializer.h"
#include "core/ptr//SharePtr.h"
BEGIN_OGS_NAMESPACE

template<typename CLS, typename FieldType>
class ReflexClassSharePtrField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = SharePtr<FieldType> CLS::*;
	ReflexClassPtrField(ReflexClassBase* cls, const char* name, FieldPtr member)
		: ReflexClassMemberBase<CLS>(cls, name)
		, m_member(member)
	{

	}

	virtual void GetObjectValue(CLS* obj, void* value) override
	{
		(*(SharePtr<FieldType>*)value) = obj->*m_member;
	}

	virtual void SetObjectValue(CLS* obj, void* value) override
	{
		obj->*m_member = *((SharePtr<FieldType>*)value);
	}

	virtual bool Serialize(CLS* obj, JSON& json) override
	{
		SharePtr<FieldType> value = (obj->*m_member);
		if (value == nullptr) return true;

		return FieldSerialize::Serialize(json[m_name], value);
	}

	virtual bool Deserialize(CLS* obj, const JSON& json) override
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