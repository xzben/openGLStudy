#pragma once

#include "macro.h"
#include "define.h"
#include "core/base/runtime.h"

BEGIN_OGS_NAMESPACE
class WeakLinker;

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
	DECLARE_RUNTIME_CLASS_BASE(Object);
public:
	template<typename T>
	friend class AutoRef;

	template<typename T>
	friend class WeakRef;

	Object();
	virtual ~Object();
	virtual bool init() { return true; }
	virtual void handleInit() {};

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
	void release();

	void addRef()
	{
		m_refcount++;
	}

	void delRef()
	{
		ASSERT(m_refcount > 0, "refcount must > 0");
		m_refcount--;

		if (m_refcount <= 0)
		{
			release();
		}
	}
private:
	WeakLinker* getLinker();
protected:
	int m_refcount{ 0 };
	WeakLinker* m_linker{ nullptr };
};

END_OGS_NAMESPACE