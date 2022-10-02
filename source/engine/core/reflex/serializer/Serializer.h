#pragma once

#include "define.h"
#include "core/reflex/reflex_define.h"

BEGIN_OGS_NAMESPACE

class Serializer
{
public:
	template<typename CLS>
	static bool Parse(CLS* obj, const std::string& path)
	{
		if (!FileSystem::GetInstance()->isFileExists(path))
		{
			return false;
		}

		std::string content = FileSystem::GetInstance()->getString(path);
		Json::Value root;
		Json::Reader reader;
		reader.parse(content, root);

		return Parse(obj, root);
	}

	template<typename CLS>
	static bool Parse(CLS* obj, const JSON& json)
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
			if (!parent->Deserialize(obj, *pJson))
			{
				return false;
			}

			parent = parent->m_parent;
			if (parent)
			{
				pJson = &(*pJson)[CLASS_SUPER_KEY];
			}
		}

		return true;
	}

	template<typename CLS>
	static bool Serialize(CLS* obj, const std::string& path)
	{
		Json::Value root;
		if (!Serialize(obj, root))
			return false;

		Json::StyledWriter swriter;
		return FileSystem::GetInstance()->writeString(path, swriter.write(root).c_str());
	}

	template<typename CLS>
	static bool Serialize(CLS* obj, JSON& json)
	{
		ReflexClassBase* parent = CLS::GetREFLEX();
		JSON* pJson = &json;

		while (parent)
		{
			if (!parent->Serialize(obj, *pJson))
			{
				return false;
			}
			parent = parent->m_parent;
			if (parent)
			{
				pJson = &(*pJson)[CLASS_SUPER_KEY];
			}
		}

		return true;
	}

	template<typename CLS>
	static CLS* Deserialize(const std::string& path)
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

	static void* Deserialize(const JSON& json);

	template<typename CLS>
	static CLS* Deserialize(const JSON& json)
	{
		void* obj = Deserialize(json);
		return static_cast<CLS*>(obj);
	}
};
END_OGS_NAMESPACE