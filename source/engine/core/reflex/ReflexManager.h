#pragma once

#include "core/tool/Singleton.h"
#include "ReflexItem.h"
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

	template<typename CLS>
	bool Serialize(CLS* obj, const std::string& path)
	{
		Json::Value root;
		if (!Serialize(obj, root))
			return false;

		Json::StyledWriter swriter;
		return FileSystem::GetInstance()->writeString(path, swriter.write(root).c_str());
	}

	template<typename CLS>
	bool Serialize(CLS* obj, JSON& json)
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

		return true;
	}

	template<typename CLS>
	bool Parse(const std::string& path)
	{
		if (!FileSystem::GetInstance()->isFileExists(path))
		{
			return nullptr;
		}

		std::string content = FileSystem::GetInstance()->getString(path);
		Json::Value root;
		Json::Reader reader;
		reader.parse(content, root);

		return Parse(root);
	}

	template<typename CLS>
	bool Parse(CLS* obj, const JSON& json)
	{
		if (!json.isMember(CLASS_OBJ_KEY))
		{
			return false;
		}
		const char* objname = json[CLASS_OBJ_KEY].asCString();

		if (obj == nullptr)
			return false;

		ReflexClassBase* cls = CLS::GetREFLEX();
		if (cls->GetName() != std::string(objname))
		{
			return false;
		}

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

		return true;
	}

	template<typename CLS>
	CLS* Deserialize(const std::string& path)
	{
		if (!FileSystem::GetInstance()->isFileExists(path))
		{
			return nullptr;
		}
		
		std::string content = FileSystem::GetInstance()->getString(path);
		Json::Value root;
		Json::Reader reader;
		reader.parse(content, root);

		return Deserialize<CLS>(root);
	}
	
	void* Deserialize(const JSON& json)
	{
		if (!json.isMember(CLASS_OBJ_KEY))
			return nullptr;

		const char* objname = json[CLASS_OBJ_KEY].asCString();
		ReflexClassBase* cls = GetReflexClass(objname);
		if (cls == nullptr)
			return nullptr;

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