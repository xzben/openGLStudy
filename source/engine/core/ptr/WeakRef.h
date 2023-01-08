#pragma once

#include "define.h"
#include "core/base/Object.h"
#include "AutoRef.h"
BEGIN_OGS_NAMESPACE

class WeakLinker
{
public:
	int m_weakcount{ 0 };
	Object*  m_obj{ nullptr};
};

template<typename T>
class WeakRef
{
public:
	template<typename TT>
	friend class AutoRef;

	template<typename TT>
	friend class WeakRef;

	friend bool operator==(T* obj, const WeakRef<T>& p);
	friend bool operator!=(T* obj, const WeakRef<T>& p);

	WeakRef()
	{

	}

	WeakRef(const AutoRef<T>& other)
	{
		if (other.m_obj)
		{
			setObject(((Object*)other.m_obj)->getLinker());
		}
			
	}

	WeakRef(T* obj)
	{
		if (obj)
		{
			setObject(((Object*)obj)->getLinker());
		}
	}

	~WeakRef()
	{
		release();
	}

	WeakRef(WeakRef<T>&& other)
	{
		setObject(other.m_linker);
		other.m_linker = nullptr;
	}

	WeakRef(WeakRef<T>& other)
	{
		setObject(other.m_linker);
	}

	template<typename NewT>
	WeakRef(const WeakRef<NewT>& other)
	{
		setObject(other.m_linker);
	}

	WeakRef<T>& operator=(WeakRef<T>& other)
	{
		setObject(other.m_linker);
	}

	WeakRef<T>& operator=(T* obj)
	{
		if(obj)
			setObject(obj->getLinker());

		return *this;
	}

	operator bool() const
	{
		return !expired();
	}

	T* operator->() const
	{
		return get();
	}

	bool operator==(T* obj) const
	{
		return obj == get();
	}

	bool operator!=(T* obj) const
	{
		return obj != get();
	}

	T* get() const
	{
		if (expired())
		{
			return nullptr;
		}

		return static_cast<T*>(m_linker->m_obj);
	}

	bool expired() const
	{
		if (m_linker == nullptr || m_linker->m_obj == nullptr)
		{
			return true;
		}

		return false;
	}

	void release()
	{
		if (m_linker)
		{
			m_linker->m_weakcount--;
			if (m_linker->m_obj == nullptr && m_linker->m_weakcount <= 0)
			{
				delete m_linker;
			}
			m_linker = nullptr;
		}
	}
private:
	
	void setObject(WeakLinker* linker)
	{
		release();
		m_linker = linker;
		if (linker)
		{
			m_linker->m_weakcount++;
		}
	}
protected:
	WeakLinker* m_linker{ nullptr };
};

template<typename T>
bool operator==(T* obj, const WeakRef<T>& p)
{
	return obj == p.get();
}

template<typename T>
bool operator!=(T* obj, const WeakRef<T>& p)
{
	return obj != p.get();
}


END_OGS_NAMESPACE