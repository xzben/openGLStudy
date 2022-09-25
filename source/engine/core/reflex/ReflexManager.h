#pragma once

#include "core/tool/Singleton.h"
#include "reflexClass.h"
#include "core/filesystem/FileSystem.h"
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