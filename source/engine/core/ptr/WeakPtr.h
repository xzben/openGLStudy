#pragma once

#include "SharePtr.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class WeakPtr final
{
public:
	template<typename TT>
	friend class SharePtr;

	template<typename TT>
	friend class WeakPtr;

	friend bool operator==(std::nullptr_t nil, const WeakPtr<T>& right);

	WeakPtr() {};

	~WeakPtr() {
		release();
	}

	WeakPtr(std::nullptr_t)
	{
		m_data = nullptr;
		m_count = nullptr;
	}

	WeakPtr(const SharePtr<T>& ptr) 
	{
		m_data = ptr.m_data;
		m_count = ptr.m_count;
		if (m_data)
		{
			ASSERT(m_count, "count must valid when m_data isvalid");
			m_count->weak++;
		}
	}

	WeakPtr(WeakPtr<T>&& other)
	{
		m_data = other.m_data;
		m_count = other.m_count;
		other.m_data = nullptr;
		other.m_count = nullptr;
	}

	WeakPtr(const WeakPtr<T>& other) 
	{
		if (!other.expired())
		{
			m_data = other.m_data;
			m_count = other.m_count;
		}
		else
		{
			m_data = nullptr;
			m_count = nullptr;
		}

		if (m_data)
		{
			ASSERT(m_count, "count must valid when m_data isvalid");
			m_count->weak++;
		}
	}

	WeakPtr<T>& operator=(const SharePtr<T>& other)
	{
		release();

		m_data = other.m_data;
		m_count = other.m_count;
		if (m_data)
		{
			ASSERT(m_count, "count must valid when m_data isvalid");
			m_count->weak++;
		}

		return *this;
	}

	bool operator ==( const WeakPtr<T>& rhs)const
	{
		return m_data = rhs.m_data;
	}

	bool operator==(std::nullptr_t nil)const 
	{
		return m_data == nullptr;
	}

	template<typename NewT>
	operator WeakPtr<NewT>() const
	{
		return ToCast<NewT>();
	}

	WeakPtr<T>& operator=(const WeakPtr<T>& other)
	{
		release();
		if (!other.expired())
		{
			m_data = other.m_data;
			m_count = other.m_count;
		}
		else
		{
			m_data = nullptr;
			m_count = nullptr;
		}

		if (m_data)
		{
			ASSERT(m_count, "count must valid when m_data isvalid");
			m_count->weak++;
		}

		return *this;
	}

	SharePtr<T> lock()
	{
		return SharePtr<T>(*this);
	}
	
	operator bool() const
	{
		return !expired();
	}

	operator T*()
	{
		return get();
	}

	T* operator->() const
	{
		return get();
	}

	T* get() const
	{
		if (!expired())
		{
			return m_data;
		}

		return nullptr;
	}

	//指针是否过期
	bool expired() const
	{
		if (m_data && m_count)
		{
			if (m_count->share > 0)
			{
				return false;
			}
		}

		return true;
	}

	void release()
	{
		if (nullptr != m_count)
		{
			m_count->weak--;
			if (m_count->weak <= 0 && m_count->share <= 0)
			{
				SAFE_DELTE(m_count);
			}
		}

		m_count = nullptr;
		m_data = nullptr;
	}
protected:
	template<typename NewT>
	WeakPtr<NewT> ToCast() const
	{
		WeakPtr<NewT> ret;
		if (!expired())
		{
			ret.m_data = static_cast<NewT*>(m_data);
			m_count->weak++;
			ret.m_count = m_count;
		}

		return std::move(ret);
	}
private:
	T* m_data = nullptr;
	Counter* m_count = nullptr;
};

template<typename T>
bool operator==(std::nullptr_t nil, const WeakPtr<T>& right)
{
	return right.m_data == nullptr;
}

END_OGS_NAMESPACE