#pragma once


#include "common.h"
#include "json/json.h"
#include <functional>
#include <unordered_map>
BEGIN_OGS_NAMESPACE

#define CLASS_OBJ_KEY	"__$classname$__"
#define CLASS_SUPER_KEY "__$superclass$__"

class Object;

using JSON = Json::Value;

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

template<typename FieldType>
class FieldSerialize
{
public:
	static void Serialize(JSON& json, FieldType* field, const std::string& name)
	{
		json[name] = *field;
	}
	static void Deserialize(const JSON& json, FieldType* field, const std::string& name)
	{
		 *field = json[name].as<FieldType>();
	}
};

class ReflexClassBase;

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

	virtual void Serialize(CLS* obj, JSON& json) = 0;
	virtual void Deserialize(CLS* obj, const JSON& json) = 0;

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
	template<typename CLS>
	friend class ReflexClassMemberBase;
	friend class ReflexManager;
	ReflexClassBase(const char* name, ReflexClassBase* parent = nullptr) : m_parent(parent) 
	{
		m_name = name;
	}

	virtual ~ReflexClassBase() = default;

	virtual void Serialize(void* obj, JSON& json)  = 0;
	virtual void Deserialize(void* obj, const JSON& json) = 0;
	virtual void* NewInstance() = 0;
	const std::string& GetName() { return m_name; }
protected:
	std::string m_name;
	ReflexClassBase* m_parent = nullptr; //∏∏¿‡
};

template<typename CLS>
class ReflexClass : public ReflexClassBase
{
public:
	ReflexClass(const char* name, ReflexClassBase* parent = nullptr)
		: ReflexClassBase(name, parent)
	{
	}

	virtual void* NewInstance() override
	{
		return new CLS();
	}

	template<typename MemberType>
	void RegisterMember(const char* fieldname, MemberType CLS::* ptrmeber)
	{
		auto item = new ReflexClassCommonField<CLS, MemberType>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	virtual void Serialize(void* obj, JSON& json) override
	{
		json[CLASS_OBJ_KEY] = this->m_name;
		for (auto item : m_members)
		{
			item.second->Serialize(static_cast<CLS*>(obj), json);
		}
	}

	virtual void Deserialize(void* obj, const JSON& json) override
	{
		std::string classname = json[CLASS_OBJ_KEY].asCString();
		ASSERT(classname == this->m_name, "muset been same class name");

		for (auto item : m_members)
		{
			item.second->Deserialize(static_cast<CLS*>(obj), json);
		}
	}
private:
	std::unordered_map<std::string, ReflexClassMemberBase<CLS>*> m_members;
};


class StaticRunObject
{
public:
	using AutoFunc = std::function<void(void)>;
	StaticRunObject(AutoFunc func) {
		func();
	}
};

END_OGS_NAMESPACE
