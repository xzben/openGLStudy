#pragma once

#include "common.h"
#include "SharePtr.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class WeakPtr final
{
public:
	friend class SharePtr<T>;

	WeakPtr() = delete;
	~WeakPtr() {
		release();
	}

	explicit WeakPtr(const SharePtr<T>& ptr){
		m_data = ptr.m_data;
		m_count = ptr.m_count;
		m_count->weak++;
	}

	explicit WeakPtr(const WeakPtr<T>& ptr) {
		m_data = ptr.m_data;
		m_count = ptr.m_count;
		m_count->weak++;
	}

	WeakPtr<T>& operator=(const SharePtr<T>& other)
	{
		release();

		m_data = other.m_data;
		m_count = other.m_count;
		m_count->weak++;
	}

	WeakPtr<T>& operator=(const WeakPtr<T>& other)
	{
		release();

		m_data = other.m_data;
		m_count = other.m_count;
		m_count->weak++;
	}

	SharePtr<T> lock()
	{
		return SharePtr<T>(*this);
	}

	T* get()
	{
		if(!expired())
		{
			return m_data;
		}

		return nullptr;
	}

	//指针是否过期
	bool expired()
	{
		if (m_count)
		{
			if (m_count->share > 0)
			{
				return false;
			}
		}

		return true;
	}
private:
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
private:
	T* m_data;
	SharePtr<T>::Counter* m_count;
};

END_OGS_NAMESPACE