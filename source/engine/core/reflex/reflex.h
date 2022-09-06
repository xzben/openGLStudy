#pragma once

#include "define.h"
#include "core/base/runtime.h"
#include "core/reflex/ReflexItem.h"
#include "core/reflex/ReflexCommon.h"
#include "core/reflex/ReflexManager.h"

#define REFLEX_TYPE_FUNC(CLS) \
void FieldSerialize<CLS>::Serialize(JSON& json, CLS* field, const std::string& name) \
{\
	CLS::GetREFLEX()->Serialize(field, json[name]); \
}\
void FieldSerialize<CLS>::Deserialize(const JSON& json, CLS* field, const std::string& name) \
{\
	CLS::GetREFLEX()->Deserialize(field, json[name]); \
}


/// reflex define base
#define DECLARE_REFLEX_CLASS( CLS ) \
public:\
	static ReflexClass<CLS>  Reflex##CLS##Obj; \
	static ReflexClassBase* GetREFLEX() { return &Reflex##CLS##Obj; } \
	virtual ReflexClassBase* GetReflex() { return &Reflex##CLS##Obj;} \
private:

#define IMPLEMENT_REFLEX_CLASS_BASE( CLS, ...) \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS);\
	static StaticRunObject Static##CLS##RegsiterReflexClass([]() { \
		ReflexManager::GetInstance()->RegisterReflexClass(#CLS, CLS::GetREFLEX()); \
	});

// reflex define with super
#define IMPLEMENT_REFLEX_CLASS( CLS ) \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS, CLS::Super::GetREFLEX()); \
	static StaticRunObject Static##CLS##RegsiterReflexClass([]() { \
		ReflexManager::GetInstance()->RegisterReflexClass(#CLS, CLS::GetREFLEX()); \
	});

/// full define base
#define DECLARE_CLASS_BASE( CLS ) \
public: \
	DECLARE_RUNTIME_CLASS_BASE( CLS ) \
	DECLARE_REFLEX_CLASS( CLS )\
private:

#define IMPLEMENT_CLASS_BASE( CLS ) \
	IMPLEMENT_RUNTIME_CLASS_BASE( CLS ) \
	IMPLEMENT_REFLEX_CLASS_BASE( CLS )

// full define with super

#define DECLARE_CLASS( CLS ) \
public : \
	DECLARE_RUNTIME_CLASS(CLS) \
	DECLARE_REFLEX_CLASS(CLS) \
private:


#define IMPLEMENT_CLASS( CLS ) \
	IMPLEMENT_RUNTIME_CLASS( CLS ) \
	IMPLEMENT_REFLEX_CLASS( CLS )


#define DECLARE_REFLEX_CLASS_FIELD(CLS)  static StaticRunObject Static##CLS##RegsiterReflexClassField;

#define BEGIN_REFLEX_CLASS_FIELD(CLS)\
	StaticRunObject CLS::Static##CLS##RegsiterReflexClassField([]() { \
		using CUR_TYPE = CLS;

#define REFLEX_FIELD(FieldType, field) ReflexManager::GetInstance()->RegisterClassMember<CUR_TYPE, FieldType>(#field, &CUR_TYPE::field);
#define REFLEX_FIELD_GETSET(FieldType, name, get, set) ReflexManager::GetInstance()->RegisterClassMember<CUR_TYPE, FieldType>(#name, get, set);

#define END_REFLEX_CLASS_FIELD() \
	});