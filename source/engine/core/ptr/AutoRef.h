#pragma once

#include "define.h"
#include "core/base/Object.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class WeakRef;

template<typename T>
class  AutoRef
{
public:
	template<typename TT>
	friend class WeakRef;

	template<typename TT>
	friend class AutoRef;


	friend bool operator==(T* obj, const AutoRef<T>& p);
	friend bool operator!=(T* obj, const AutoRef<T>& p);

	AutoRef()
	{

	}

	AutoRef(const WeakRef<T>& other)
	{
		if(other.m_linker && other.m_linker->m_obj)
			setObject(other.m_linker->m_obj->ToCast<T>());
	}

	AutoRef(T* obj)
	{
		setObject(obj);
	}

	~AutoRef()
	{
		release();
	}

	AutoRef(AutoRef<T>&& other)
	{
		setObject(other.m_obj);
		other.m_obj = nullptr;
	}

	AutoRef(const AutoRef<T>& other)
	{
		setObject(other.m_obj);
	}

	template<typename NewT>
	AutoRef(const AutoRef<NewT>& other)
	{
		if (other.m_obj)
			setObject(other.m_obj->ToCast<T>());
	}

	template<typename NewT>
	AutoRef<NewT> ToCast() const
	{
		AutoRef<NewT> ret;
		NewT* obj = dynamic_cast<NewT*>(m_obj);
		if (obj)
		{
			ret.setObject(obj);
		}

		return std::move(ret);
	}

	T* get() const
	{
		return m_obj;
	}

	T* operator->() const
	{
		return get();
	}

	AutoRef<T>& operator=(const AutoRef<T>& other)
	{
		setObject(other.m_obj);
		return *this;
	}

	AutoRef<T>& operator=(T* obj)
	{
		setObject(obj);
		return *this;
	}

	bool operator ==(T* obj) const
	{
		return m_obj == obj;
	}

	bool operator!= (T* obj) const
	{
		return m_obj != obj;
	}

	operator bool() const
	{
		return m_obj != nullptr;
	}

	void release()
	{
		if (m_obj)
		{
			((Object*)m_obj)->delRef();
		}
		m_obj = nullptr;

	}
protected:
	void setObject(T* obj)
	{
		release();
		m_obj = obj;
		if (m_obj)
		{
			((Object*)m_obj)->addRef();
		}
			
	}
private:
	T* m_obj{ nullptr };
};

template<typename T>
bool operator==(T* obj, const AutoRef<T>& p)
{
	return obj == p.m_obj;
}

template<typename T>
bool operator!=(T* obj, const AutoRef<T>& p)
{
	return obj != p.m_obj;
}

END_OGS_NAMESPACE