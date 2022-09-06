#pragma once

#include "core/tool/Singleton.h"
#include "ReflexItem.h"
#include <unordered_map>
BEGIN_OGS_NAMESPACE

class ReflexManager : public Singleton<ReflexManager>
{
public:
	ReflexManager() = default;

	void RegisterReflexClass(const char* classname, ReflexClassBase* cls)
	{
		m_classes.insert(std::make_pair(classname, cls));
	}

	template<typename CLS>
	ReflexClass<CLS>* GetReflexClass()
	{
		return static_cast<ReflexClass<CLS>*>(CLS::GetREFLEX());
	}

	ReflexClassBase* GetReflexClass(const char* classname)
	{
		auto it = m_classes.find(classname);

		if (it == m_classes.end())
		{
			return nullptr;
		}

		return it->second;
	}

	template<typename CLS>
	void Serialize(CLS* obj, JSON& json)
	{
		ReflexClassBase* parent = CLS::GetREFLEX();
		JSON* pJson = &json;

		while (parent)
		{
			parent->Serialize(obj, *pJson);
			parent = parent->m_parent;
			if (parent)
			{
				pJson = &(*pJson)[CLASS_SUPER_KEY];
			}	
		}
	}

	void* Deserialize(const JSON& json)
	{
		const char* objname = json[CLASS_OBJ_KEY].asCString();
		ReflexClassBase* cls = GetReflexClass(objname);
		void* obj = cls->NewInstance();

		ReflexClassBase* parent = cls;
		const JSON* pJson = &json;
		while (parent)
		{
			parent->Deserialize(obj, *pJson);
			parent = parent->m_parent;
			if (parent)
			{
				pJson = &(*pJson)[CLASS_SUPER_KEY];
			}
		}
		
		return obj;
	}

	template<typename CLS>
	CLS* Deserialize(const JSON& json)
	{
		void* obj = this->Deserialize(json);
		return static_cast<CLS*>(obj);
	}

	template<typename CLS, typename FieldType>
	void RegisterClassMember(const char* fieldname, FieldType CLS::* memberptr)
	{
		ReflexClass<CLS>* cls = GetReflexClass<CLS>();
		cls->RegisterMember<FieldType>(fieldname, memberptr);
	}


	template<typename CLS, typename FieldType>
	void RegisterClassMember(const char* fieldname, const FieldType& (CLS::*getfunc)()const, void (CLS::*setfunc)(const FieldType&))
	{
		ReflexClass<CLS>* cls = GetReflexClass<CLS>();
		cls->RegisterMember<FieldType>(fieldname, getfunc, setfunc);
	}
private:
	std::unordered_map<std::string, ReflexClassBase*> m_classes;
};
END_OGS_NAMESPACE