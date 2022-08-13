#pragma once

#include "common.h"
#include "ReflexItem.h"
#include "ReflexManager.h"


#define DECLARE_CLASS_BASE( CLS ) \
public : \
	typedef CLS ThisType; \
	static Runtime Runtime##CLS##Obj; \
	static ReflexClass<CLS>  Reflex##CLS##Obj; \
	static Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	static ReflexClassBase* GetREFLEX() { return &Reflex##CLS##Obj; } \
	virtual Runtime* GetRuntime() { return &Runtime##CLS##Obj; } \
	virtual ReflexClassBase* GetReflex() { return &Reflex##CLS##Obj;} \
private:

#define DECLARE_CLASS( CLS ) \
public : \
	typedef ThisType Super; \
	typedef CLS ThisType; \
	static Runtime Runtime##CLS##Obj; \
	static ReflexClass<CLS>  Reflex##CLS##Obj; \
	static Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	static ReflexClassBase* GetREFLEX() { return &Reflex##CLS##Obj; } \
	virtual Runtime* GetRuntime() { return &Runtime##CLS##Obj; } \
	virtual ReflexClassBase* GetReflex() { return &Reflex##CLS##Obj;} \
private:

#define IMPLEMENT_CLASS_BASE( CLS ) \
	Runtime CLS::Runtime##CLS##Obj(#CLS); \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS);

#define IMPLEMENT_CLASS( CLS ) \
	Runtime CLS::Runtime##CLS##Obj(#CLS, CLS::Super::GetRUNTIME()) \
	ReflexClass<CLS>  CLS::Reflex##CLS##Obj(#CLS, CLS::Super::GetREFLEX());
	