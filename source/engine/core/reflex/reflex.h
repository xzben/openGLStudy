#pragma once

#include "common.h"
#include "core/reflex/ReflexItem.h"
#include "core/reflex/ReflexManager.h"

/// Runtime define base
#define DECLARE_RUNTIME_CLASS_BASE(CLS) \
	typedef CLS ThisType; \
	static Runtime Runtime##CLS##Obj; \
	static Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	virtual Runtime* GetRuntime() { return &Runtime##CLS##Obj; }

#define IMPLEMENT_RUNTIME_CLASS_BASE( CLS ) \
	Runtime CLS::Runtime##CLS##Obj(#CLS);

/// runtime define with super
#define DECLARE_RUNTIME_CLASS( CLS ) \
	typedef ThisType Super; \
	DECLARE_RUNTIME_CLASS_BASE(CLS)

#define IMPLEMENT_RUNTIME_CLASS(CLS) \
	Runtime CLS::Runtime##CLS##Obj(#CLS, CLS::Super::GetRUNTIME());

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
	static ReflexClass<CLS>  Reflex##CLS##Obj; \
	static ReflexClassBase* GetREFLEX() { return &Reflex##CLS##Obj; } \
	virtual ReflexClassBase* GetReflex() { return &Reflex##CLS##Obj;}

#define IMPLEMENT_REFLEX_CLASS_BASE( CLS ) \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS);\
	REFLEX_TYPE_FUNC(CLS) \
	static StaticRunObject Static##CLS##RegsiterReflexClass([]() { \
		ReflexManager::GetInstance()->RegisterReflexClass(#CLS, CLS::GetREFLEX()); \
	});

// reflex define with super
#define IMPLEMENT_REFLEX_CLASS( CLS ) \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS, CLS::Super::GetREFLEX()); \
	REFLEX_TYPE_FUNC(CLS) \
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

	
#define BEGIN_REFLEX_CLASS_FIELD(CLS)\
	static StaticRunObject Static##CLS##RegsiterReflexClassField([]() { \

#define REFLEX_FIELD(CLS, field) \
	ReflexManager::GetInstance()->RegisterClassMember<CLS, decltype(CLS::field)>(#field, &CLS::field);

#define END_REFLEX_CLASS_FIELD()\
	});