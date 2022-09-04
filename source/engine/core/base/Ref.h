#pragma once

#include "macro.h"
#include "common.h"
#include "core/reflex/reflex.h"

BEGIN_OGS_NAMESPACE

class NoCopy
{
protected:
	NoCopy() = default;
	~NoCopy() = default;
public:
	NoCopy(const NoCopy& r) = delete;
	NoCopy& operator=(const NoCopy& r) = delete;
};

class Object
{
	DECLARE_RUNTIME_CLASS_BASE(Object)
public:
	Object() = default;
	virtual ~Object() = default;

	template<typename CLS>
	bool IsKindOf()
	{
		Runtime* runtime = this->GetRuntime();
		Runtime* clsruntime = CLS::GetRUNTIME();

		while(runtime)
		{
			if (runtime == clsruntime)
			{
				return true;
			}
			runtime = runtime->m_pBase;
		}

		return false;
	}

	template<typename CLS>
	CLS* ToCast()
	{
		return this->IsKindOf<CLS>() ? dynamic_cast<CLS*>(this) : nullptr;
	}
};

class Ref : public Object
{
public:
	typedef Object Supper;
	typedef Ref ThisType;

	Ref() = default;
	virtual ~Ref() = default;
};

END_OGS_NAMESPACE