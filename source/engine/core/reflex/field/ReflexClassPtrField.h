/*
	ָ��ķ��䣬��һ���Ƚ�����Ĺ��̣���Ϊָ���ǿ��ܶ������ָ��һ��ָ��ġ�
	����������ָ��ķ�������Ҫע����Ǽ򵥵ĳ��й������ֱ�����Եķ�ʽ���з��䣬
	�����Ƹ��ӵ�ָ�빲��ʽ����Ҫ����ҵ��ͨ�� ���� ClassGetSetField �ķ�ʽ���з�������л��뷴���л���
	ͨ���� set �ӿ���ȥ������Ҫ���й���ָ������ҵ��
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