#pragma once

namespace OGS {
	class Runtime
	{
	public:
		friend class Object;
		Runtime(const char* name, Runtime* pbase = nullptr)
			: m_name(name)
			, m_pBase(pbase)
		{

		};
		virtual Runtime* GetBaseRTTS()
		{
			return m_pBase;
		}

		const std::string& getName()
		{
			return m_name;
		}
	private:
		Runtime* m_pBase;
		std::string m_name;
	};
}

// create func declare
#define DECLARE_CREATE_FUN(CLS) \
public: \
	template<typename ...Args> \
	static CLS* create(const Args&... args)\
	{\
		CLS* obj = new CLS(); \
		if (!obj->init(args...)) \
		{ \
			ASSERT(false, "init failed %s", #CLS); \
			return nullptr; \
		} \
		obj->handleInit(); \
		return obj; \
	} \
private:

/// Runtime define base
#define DECLARE_RUNTIME_CLASS_BASE(CLS) \
public:\
	typedef CLS ThisType; \
	static OGS::Runtime Runtime##CLS##Obj; \
	static OGS::Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	virtual OGS::Runtime* GetRuntime() { return &Runtime##CLS##Obj; } \
	DECLARE_CREATE_FUN(CLS)




#define IMPLEMENT_RUNTIME_CLASS_BASE( CLS ) \
	OGS::Runtime CLS::Runtime##CLS##Obj(#CLS);

/// runtime define with super
#define DECLARE_RUNTIME_CLASS( CLS ) \
public: \
	typedef ThisType Super; \
	DECLARE_RUNTIME_CLASS_BASE(CLS)

#define IMPLEMENT_RUNTIME_CLASS(CLS) \
	OGS::Runtime CLS::Runtime##CLS##Obj(#CLS, CLS::Super::GetRUNTIME());

/// Runtime define base
#define DECLARE_RUNTIME_TEMPLATE_CLASS_BASE(CLS, T) \
public:\
	typedef CLS<T> ThisType; \
	static OGS::Runtime Runtime##CLS##Obj; \
	static OGS::Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	virtual OGS::Runtime* GetRuntime() { return &Runtime##CLS##Obj; } \
	DECLARE_CREATE_FUN(CLS<T>)

#define DECLARE_RUNTIME_TEMPLATE_CLASS( CLS, T) \
public: \
	typedef ThisType Super; \
	DECLARE_RUNTIME_TEMPLATE_CLASS_BASE(CLS, T)

#define IMPLEMENT_RUNTIME_TEMPLATE_CLASS(CLS, T) \
	template<T> \
	OGS::Runtime CLS<T>::Runtime##CLS##Obj(#CLS<T>, CLS::Super::GetRUNTIME());