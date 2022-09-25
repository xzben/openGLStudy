#pragma once
#include "reflex_define.h"
#include <unordered_map>

BEGIN_OGS_NAMESPACE

class ReflexClassBase
{
public:
	template<typename CLS>
	friend class ReflexClassMemberBase;
	friend class ReflexManager;
	friend class Serializer;

	ReflexClassBase(const char* name, ReflexClassBase* parent = nullptr) : m_parent(parent)
	{
		m_name = name;
	}

	virtual ~ReflexClassBase() = default;

	virtual bool Serialize(void* obj, JSON& json) = 0;
	virtual bool Deserialize(void* obj, const JSON& json) = 0;
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
	void RegisterMember(const char* fieldname, SharePtr<FieldType> CLS::* ptrmeber)
	{
		auto item = new ReflexClassPtrField<CLS, FieldType>(this, fieldname, ptrmeber);
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