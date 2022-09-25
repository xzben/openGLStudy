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
	private:
		Runtime* m_pBase;
		std::string m_name;
	};
}
/// Runtime define base
#define DECLARE_RUNTIME_CLASS_BASE(CLS) \
public:\
	typedef CLS ThisType; \
	static OGS::Runtime Runtime##CLS##Obj; \
	static OGS::Runtime* GetRUNTIME(){ return &Runtime##CLS##Obj; } \
	virtual OGS::Runtime* GetRuntime() { return &Runtime##CLS##Obj; }\
	static CLS* create(){ \
		CLS* obj = new CLS(); \
		return obj; \
	} \
private:

#define IMPLEMENT_RUNTIME_CLASS_BASE( CLS ) \
	OGS::Runtime CLS::Runtime##CLS##Obj(#CLS);

/// runtime define with super
#define DECLARE_RUNTIME_CLASS( CLS ) \
public: \
	typedef ThisType Super; \
	DECLARE_RUNTIME_CLASS_BASE(CLS)

#define IMPLEMENT_RUNTIME_CLASS(CLS) \
	OGS::Runtime CLS::Runtime##CLS##Obj(#CLS, CLS::Super::GetRUNTIME());