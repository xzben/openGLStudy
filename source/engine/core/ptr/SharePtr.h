#pragma once

#include "define.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class WeakPtr;

struct Counter
{
	Counter() :share(1), weak(1) {}
	int share;
	int weak;
};

template<typename T>
class SharePtr final
{
private:
	friend class WeakPtr<T>;

	friend class SharePtr;

	template<typename T1, typename ...Args>
	friend SharePtr<T1> makeShare(Args&&... args);

	template<typename T1>
	friend SharePtr<T1> makeShare(T1* ptr);

	template<typename T1>
	friend SharePtr<T1> makeShare();

	friend bool operator==(std::nullptr_t nil, const SharePtr<T>& right);

	SharePtr(T* ptr)
		: m_data(ptr)
	{
		ASSERT(m_data, "ptr must been valid");
		m_count = new Counter;
	}

	SharePtr(const WeakPtr<T>& other)
	{
		if (!other.expired())
		{
			m_data = other.m_data;
			m_count = other.m_count;
			m_count->share++;
			m_count->weak++;
		}
		else
		{
			m_data = nullptr;
			m_count = nullptr;
		}
	}
public:
	SharePtr(){}

	SharePtr(const SharePtr<T>& other)
	{
		m_data = other.m_data;
		m_count = other.m_count;
		if (m_data)
		{
			ASSERT(m_count, "when data isvalid count must been valid!");
			m_count->share++;
			m_count->weak++;
		}
		
	}

	SharePtr& operator=(const SharePtr<T>& other)
	{
		release();
		m_data = other.m_data;
		m_count = other.m_count;
		if (m_data)
		{
			ASSERT(m_count, "when data isvalid count must been valid!");
			m_count->share++;
			m_count->weak++;
		}
		
		return *this;
	}

	template<typename NewT>
	SharePtr<NewT> ToCast() const
	{
		SharePtr<NewT> ret;
		if (m_data)
		{
			ret.m_data = static_cast<NewT*>(m_data);
			m_count->share++;
			m_count->weak++;
			ret.m_count = m_count;
		}

		return std::move(ret);
	}

	bool operator==(const SharePtr<T>& right)const
	{
		return m_data == right.m_data;
	}

	bool operator!=(const SharePtr<T>& right) const
	{
		reeturn m_data != right.m_data;
	}

	bool operator==(std::nullptr_t nil)const
	{
		return m_data == nullptr;
	}
	
	T* operator->() const
	{
		return m_data;
	}

	template<typename NewT>
	operator SharePtr<NewT>() const
	{
		return ToCast<NewT>();
	}

	operator bool() const
	{
		return m_data != nullptr;
	}

	T* get()const 
	{
		return m_data;
	}

	virtual ~SharePtr()
	{
		release();
	}

	void release()
	{
		if (m_data == nullptr) return;
		ASSERT(m_count, "when data valid count must beed valid");
		ASSERT(m_count->share > 0, "share count must > 0 when release");
		m_count->share--;

		if (m_count->share <= 0)
		{
			SAFE_DELTE(m_data);

			m_count->weak--;
			if (m_count->weak <= 0)
			{
				SAFE_DELTE(m_count);
			}
		}
		m_data = nullptr;
		m_count = nullptr;
	}
private:
	Counter* m_count = nullptr;
	T* m_data = nullptr;
};

template<typename T>
bool operator==(std::nullptr_t nil, const SharePtr<T>& right)
{
	return right.m_data == nullptr;
}

template<typename T>
inline SharePtr<T> makeShare(T* ptr)
{
	return SharePtr<T>(ptr);
}

template<typename T>
inline SharePtr<T> makeShare()
{
	return SharePtr<T>(new T());
}

template<typename T, typename ...Args>
inline SharePtr<T> makeShare(Args... args)
{
	return SharePtr<T>(new T(args));
}

END_OGS_NAMESPACE