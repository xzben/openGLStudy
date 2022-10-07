/*
	指针的反射，是一个比较特殊的过程，因为指针是可能多个对象指向一个指针的。
	所以在这里指针的反射我们要注意的是简单的持有规则可以直接属性的方式进行反射，
	如果设计复杂的指针共享方式，需要根据业务通过 定制 ClassGetSetField 的方式进行反射的序列化与反序列化，
	通过在 set 接口中去处理需要持有共享指针对象的业务
*/
#pragma once
#include "reflexClassFieldBase.h"
#include "core/reflex/serializer/Serializer.h"
BEGIN_OGS_NAMESPACE

template<typename CLS, typename FieldType>
class ReflexClassPtrField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = FieldType* CLS::*;
	ReflexClassPtrField(ReflexClassBase* cls, const char* name, FieldPtr member, int flag)
		: ReflexClassMemberBase<CLS>(cls, name, flag)
		, m_member(member)
	{

	}

	virtual const char* getRawTypeName() override
	{
		return typeid(FieldType).name();
	}

	virtual void* getFieldData(void* obj) override
	{
		CLS* clsobj = (CLS*)obj;
		return (clsobj->*m_member);
	}

	virtual void GetObjectValue(void* obj, void* value) override
	{
		if (value == nullptr) return;
		CLS* clsobj = (CLS*)obj;
		(*(FieldType**)value) = clsobj->*m_member;
	}

	virtual void SetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		if (value == nullptr)
		{
			clsobj->*m_member = nullptr;
		}
		else
		{
			clsobj->*m_member = *((FieldType**)value);
		}
	}

	virtual bool Serialize(void* obj, JSON& json) override
	{
		CLS* clsobj = (CLS*)obj;
		FieldType* value = (clsobj->*m_member);
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
					value = nullptr;
					SetObjectValue(obj, value);
					return false;
				}
			}
		}

		SetObjectValue(obj, &value);
		return true;
	}
private:
	FieldPtr m_member;
};

END_OGS_NAMESPACE