#pragma once

#include "core/reflex/reflex_define.h"
#include "core/reflex/reflexClassBase.h"

BEGIN_OGS_NAMESPACE

class ReflexClassFieldBase
{
public:
	ReflexClassFieldBase(ReflexClassBase* cls, const char* name, int flag) 
		: m_cls(cls)
		, m_flags(flag)
		, m_rawname(name)
	{
		m_name = "$" + cls->m_name + "$." + name;
	}
	const std::string& GetRawName() { return m_rawname; }
	const std::string& GetName() { return m_name; }

	virtual void GetObjectValue(void* obj, void* value) = 0;
	virtual void SetObjectValue(void* obj, void* value) = 0;

	virtual bool Serialize(void* obj, JSON& json) = 0;
	virtual bool Deserialize(void* obj, const JSON& json) = 0;

	virtual const char*  getRawTypeName() = 0;
	virtual void* getFieldData(void* obj) = 0;

	bool isEditable() { return (m_flags & (int)ReflexConfig::NO_Edit) == 0; }
	bool isSerializeable() { return (m_flags & (int)ReflexConfig::NO_Serialize) == 0; }

protected:
	std::string m_name;
	std::string m_rawname;
	ReflexClassBase* m_cls;
	int m_flags;
};

template<typename CLS>
class ReflexClassMemberBase : public ReflexClassFieldBase
{
public:
	using CLSTYPE = CLS;
	ReflexClassMemberBase(ReflexClassBase* cls, const char* name, int flag)
		:ReflexClassFieldBase(cls, name, flag)
	{

	}

	CLS* getObjClass(void* obj)
	{
		return (CLS * (obj));
	}
};


template<typename CLS, typename FieldType>
class ReflexClassCommonField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = FieldType CLS::*;
	ReflexClassCommonField(ReflexClassBase* cls, const char* name, FieldPtr member, int flag)
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
		return &(clsobj->*m_member);
	}

	virtual void GetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		(*(FieldType*)value) = clsobj->*m_member;
	}

	virtual void SetObjectValue(void* obj, void* value) override
	{
		CLS* clsobj = (CLS*)obj;
		clsobj->*m_member = (*(FieldType*)value);
	}

	virtual bool Serialize(void* obj, JSON& json) override
	{
		CLS* clsobj = (CLS*)obj;
		return FieldSerialize::Serialize(json[m_name], &(clsobj->*m_member));
	}

	virtual bool Deserialize(void* obj, const JSON& json) override
	{
		if (!json.isMember(m_name))
		{
			ASSERT(false, "must have field [%s]", m_name.c_str());
			return false;
		}
		CLS* clsobj = (CLS*)obj;
		return FieldSerialize::Deserialize(json[m_name], &(clsobj->*m_member));
	}
private:
	FieldPtr m_member;
};

END_OGS_NAMESPACE