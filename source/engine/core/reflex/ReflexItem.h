#pragma once


#include "define.h"
#include "innerJson.h"
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <string>
#include <map>
BEGIN_OGS_NAMESPACE

#define CLASS_OBJ_KEY	"classname"
#define CLASS_SUPER_KEY "superclass"
#define MAP_KEY  "map_key"
#define MAP_VALUE  "map_value"

class Object;



namespace reflex_define
{
	template <class _Ty>
	using valid_mapkey_t = std::enable_if_t<std::_Is_any_of_v<_Ty, bool, char, int, unsigned int, float, double, JSON::Int64, JSON::UInt64, std::string>, _Ty>;
}



namespace FieldSerialize
{
	template<typename FieldType>
	void Serialize(JSON& json, FieldType* field)
	{
		FieldType::GetREFLEX()->Serialize(field, json);
	}

	template<typename FieldType>
	void Deserialize(const JSON& json, FieldType* field)
	{
		FieldType::GetREFLEX()->Deserialize(field, json);
	}

	template<typename FieldType>
	void Serialize(JSON& json, std::vector<FieldType>*field)
	{
		int size = field->size();
		json.resize(size);

		for (int i = 0; i < size; i++)
		{
			FieldSerialize::Serialize(json[i], &((*field)[i]));
		}
	}

	template<typename FieldType>
	void Deserialize(const JSON& json, std::vector<FieldType>* field)
	{
		ASSERT(json.isArray(), "must been array json object");

		int count = json.size();
		field->resize(count);
		for (int i = 0; i < count; i++)
		{
			FieldSerialize::Deserialize(json[i], &((*field)[i]));
		}
	}
	/*
	template<typename KeyType, typename FieldType>
	void Serialize(JSON& json, std::map<reflex_define::valid_mapkey_t<KeyType>, FieldType>* field)
	{
		int size = field->size();
		json.resize(size);
		int index = 0;
		for(auto it = field->begin(); it != field->end(); it++)
		{
			JSON item = json[index];
			FieldSerialize::Serialize(item[MAP_KEY], &it->first);
			FieldSerialize::Serialize(item[MAP_VALUE], &it->second);
			index++;
		}
	}

	template<typename KeyType, typename FieldType>
	void Deserialize(const JSON& json, std::map<reflex_define::valid_mapkey_t<KeyType>, FieldType>* field)
	{
		ASSERT(json.isArray(), "must been array json object");
		int size = json.size();
		for (int i = 0; i < size; i++)
		{
			KeyType key;
			FieldType value;

			const JSON& item = json[i];
			ASSERT(item.isObject(), "must been map object has key and value");
			FieldSerialize::Deserialize(item[MAP_KEY], &key);
			FieldSerialize::Deserialize(item[MAP_VALUE], &value);

			field->insert(std::make_pair(key, value));
		}
	}*/
}


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
		FieldSerialize::Serialize(json[m_name], &(obj->*m_member));
	}

	virtual void Deserialize(CLS* obj, const JSON& json) override
	{
		FieldSerialize::Deserialize(json[m_name], &(obj->*m_member));
	}
private:
	FieldPtr m_member;
};

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

	virtual void Serialize(CLS* obj, JSON& json) override
	{
		FieldType value = (obj->*m_get)();
		FieldSerialize::Serialize(json[m_name], &value);
	}

	virtual void Deserialize(CLS* obj, const JSON& json) override
	{
		FieldType value;
		FieldSerialize::Deserialize(json[m_name], &value);
		(obj->*m_set)(value);
	}
private:
	GetFunc m_get;
	SetFunc m_set;
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

	template<typename FieldType>
	void RegisterMember(const char* fieldname, FieldType CLS::* ptrmeber)
	{
		auto item = new ReflexClassCommonField<CLS, FieldType>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, const FieldType& (CLS::*getfunc)()const, void (CLS::* setfunc)(const FieldType&))
	{
		auto item = new ReflexClassGetSetField<CLS, FieldType>(this, fieldname, getfunc, setfunc);
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
