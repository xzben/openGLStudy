#pragma once
#include "reflex_define.h"
#include "reflexClassBase.h"
#include "ReflexClassField.h"
#include "core/ptr/WeakRef.h"
#include "core/ptr/AutoRef.h"
#include <unordered_map>

BEGIN_OGS_NAMESPACE

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
		auto obj = new CLS();
		return obj;
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, std::remove_pointer_t<FieldType> CLS::* ptrmeber)
	{
		auto item = new ReflexClassCommonField<CLS, std::remove_pointer_t<FieldType>>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, std::remove_pointer_t<FieldType>* CLS::* ptrmeber)
	{
		auto item = new ReflexClassPtrField<CLS, std::remove_pointer_t<FieldType>>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, AutoRef<FieldType> CLS::* ptrmeber)
	{
		auto item = new ReflexClassAutoRefPtrField<CLS, FieldType>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, WeakRef<FieldType> CLS::* ptrmeber)
	{
		auto item = new ReflexClassWeakRefPtrField<CLS, FieldType>(this, fieldname, ptrmeber);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	template<typename FieldType>
	void RegisterMember(const char* fieldname, const FieldType& (CLS::* getfunc)()const, void (CLS::* setfunc)(const FieldType&))
	{
		auto item = new ReflexClassGetSetField<CLS, FieldType>(this, fieldname, getfunc, setfunc);
		m_members.insert(std::make_pair<std::string, ReflexClassMemberBase<CLS>*>(fieldname, item));
	}

	virtual bool Serialize(void* obj, JSON& json) override
	{
		json[CLASS_OBJ_KEY] = this->m_name;
		for (auto item : m_members)
		{
			if (!item.second->Serialize(static_cast<CLS*>(obj), json))
			{
				return false;
			}
		}

		return true;
	}

	virtual bool Deserialize(void* obj, const JSON& json) override
	{
		if (!json.isMember(CLASS_OBJ_KEY))
		{
			ASSERT(false, "Must has member %s", CLASS_OBJ_KEY);
			return false;
		}
		std::string classname = json[CLASS_OBJ_KEY].asCString();
		if (classname != this->m_name)
		{
			ASSERT(false, "muset been same class name");
			return false;
		}

		for (auto item : m_members)
		{
			if (!item.second->Deserialize(static_cast<CLS*>(obj), json))
			{
				return false;
			}
		}

		return true;
	}
private:
	std::unordered_map<std::string, ReflexClassMemberBase<CLS>*> m_members;
};

END_OGS_NAMESPACE