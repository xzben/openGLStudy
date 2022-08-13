#pragma once


#include "common.h"
#include <functional>
#include <unordered_map>
BEGIN_OGS_NAMESPACE

class Object;

class Runtime
{
public:
	Runtime(const char* name, Runtime* pbase = nullptr)
		: m_name(name)
		,m_pBase(pbase)
	{
	};
	virtual Runtime* GetBaseRTTS()
	{
		return m_pBase;
	}
private:
	Runtime* m_pBase;
	std::string m_name;
};

typedef std::string JSON;

template<typename FieldType>
class FieldSerialize
{
public:
	static void Serialize(JSON& json, FieldType* field, const std::string& name)
	{
		ASSERT(false, "need to implement by use type");
	}
	static void Deserialize(const JSON& json, FieldType* field, const std::string& name)
	{
		ASSERT(false, "need to implement by use type");
	}
};

template<typename CLS>
class ReflexClassMemberBase
{
public:
	ReflexClassMemberBase(const char* name) :m_name(name) {}
	virtual ~ReflexClassMemberBase() = default;

	virtual void GetObjectValue(CLS* obj, void* value) = 0;
	virtual void SetObjectValue(CLS* obj, void* value) = 0;

	virtual void Serialize(CLS* obj, JSON& json) = 0;
	virtual void Deserialize(CLS* obj, const JSON& json) = 0;

	const std::string& GetName() { return m_name; }
protected:
	std::string m_name;
};


template<typename CLS, typename FieldType>
class ReflexClassField : public ReflexClassMemberBase<CLS>
{
public:
	using FieldPtr = FieldType CLS::*;

	ReflexClassField(const char* name, FieldPtr member)
		: ReflexClassMemberBase<CLS>(name)
		, m_member(member)
	{

	}

	virtual void GetObjectValue(CLS* obj, void* value) override
	{
		(*(FieldType *)value) = obj->*m_member;
	}

	virtual void SetObjectValue(CLS* obj, void* value) override
	{
		 obj->*m_member = (*(FieldType*)value);
	}

	virtual void Serialize(CLS* obj, JSON& json) override
	{
		FieldSerialize<FieldType>::Serialize(json, &(obj->*m_member), m_name);
	}

	virtual void Deserialize(CLS* obj, const JSON& json) override
	{
		FieldSerialize<FieldType>::Deserialize(json, &(obj->*m_member), m_name);
	}
private:
	FieldPtr m_member;
};


class ReflexClassBase
{
public:
	ReflexClassBase(const char* name) :m_name(name) {}
	virtual ~ReflexClassBase() = default;

	virtual void Serialize(Object* obj, JSON& json)  = 0;
	virtual void Deserialize(Object* obj, const JSON& json) = 0;
	const std::string& GetName() { return m_name; }
protected:
	std::string m_name;
};

template<typename CLS>
class ReflexClass : public ReflexClassBase
{
public:
	ReflexClass(const char* name, ReflexClassBase* parent = nullptr)
		: ReflexClassBase(name)
		, m_parent(parent)
	{
	}

	template<typename MemberType>
	void RegisterMember(const char* fieldname, MemberType CLS::* ptrmeber)
	{
		auto item = new ReflexClassField<CLS, MemberType>(fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	virtual void Serialize(Object* obj, JSON& json) override
	{
		json += m_name + "|";
		for (auto item : m_members)
		{
			item.second->Serialize(static_cast<CLS*>(obj), json);
		}
	}

	virtual void Deserialize(Object* obj, const JSON& json) override
	{
		for (auto item : m_members)
		{
			item.second->Deserialize(static_cast<CLS*>(obj), json);
		}
	}
private:
	std::unordered_map<std::string, ReflexClassMemberBase<CLS>*> m_members;
	ReflexClassBase* m_parent = nullptr; //∏∏¿‡
};



END_OGS_NAMESPACE
