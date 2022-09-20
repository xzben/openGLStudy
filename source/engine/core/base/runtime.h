#pragma once

class Runtime
{
public:
	Runtime(const char* name, Runtime* pbase = nullptr)
		: m_name(name)
		, m_pBase(pbase)
	{

	};
	virtual Runtime* GetBaseRTTS()
	{
		return m_pBase;
	}
private:
	Runtime* m_pBase;
	std::string m_name;
};

/// Runtime define base
#define DECLARE_RUNTIME_CLASS_BASE(CLS) \
public:\
	typedef CLS ThisType; \
	static Runtime Runtime##CLS##Obj; \
	static Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	virtual Runtime* GetRuntime() { return &Runtime##CLS##Obj; }\
	static CLS* create(){ return new CLS();} \
private:

#define IMPLEMENT_RUNTIME_CLASS_BASE( CLS ) \
	Runtime CLS::Runtime##CLS##Obj(#CLS);

/// runtime define with super
#define DECLARE_RUNTIME_CLASS( CLS ) \
public: \
	typedef ThisType Super; \
	DECLARE_RUNTIME_CLASS_BASE(CLS)

#define IMPLEMENT_RUNTIME_CLASS(CLS) \
	Runtime CLS::Runtime##CLS##Obj(#CLS, CLS::Super::GetRUNTIME());