#pragma once

#include "common.h"
#include "WeakPtr.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class SharePtr final
{
public:
	friend class WeakPtr<T>;
	SharePtr() = delete;

	explicit SharePtr(T* ptr) 
		: m_data(ptr)
		, m_count(new Counter) 
	{
		ASSERT(ptr != nullptr, "ptr must been valid");
	}

	SharePtr(const SharePtr<T>& other)
	{
		m_data = other.m_data;
		m_count = other.m_count;
		m_count->share++;
	}

	SharePtr(const WeakPtr<T>& other)
	{
		m_data = other.m_data;
		m_count = other.m_count;
		m_count->share++;
	}

	SharePtr& operator=(const WeakPtr<T>& other)
	{
		release();
		m_data = other.m_data;
		m_count = other.m_count;
		m_count->share++;

		return *this;
	}
	SharePtr& operator=(const SharePtr<T>& other)
	{
		release();
		m_data = other->m_data;
		m_count = other->m_count;
		m_count->share++;

		return *this;
	}

	T& operator*()
	{
		return *m_data;
	}
	
	T* operator->()
	{
		return m_data;
	}

	virtual ~SharePtr()
	{
		release();
	}

	struct Counter
	{
		Counter() :share(1), weak(0) {}
		int share;
		int weak;
	};

private:
	void release()
	{
		ASSERT(m_count->share > 0, "share count must > 0 when release");
		m_count->share--;

		if (m_count->share <= 0)
		{
			SAFE_DELTE(m_data);
		}

		if (m_count->weak <= 0)
		{
			SAFE_DELTE(m_count);
		}
	}
private:
	Counter* m_count : nullptr;
	T* m_data;
};

END_OGS_NAMESPACE