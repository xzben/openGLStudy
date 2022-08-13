#pragma once

#include <mutex>
#include <condition_variable>

#include "common.h"

BEGIN_OGS_NAMESPACE

class Semaphore final
{
public:
	Semaphore():m_count(0), m_wakeups(0){}

	void wait() 
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_count--;
		if (m_count < 0)
		{
			m_condition.wait(lock, [&]()->bool { return m_wakeups > 0; });
			--m_wakeups;
		}
	}

	void signal()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_count++;
		if (m_count <= 0)
		{
			++m_wakeups;
			m_condition.notify_one();
		}
	}

	void signalAll()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_wakeups = abs(m_count);
		m_count = 0;
		m_condition.notify_all();
	}

private:
	int m_count;
	int m_wakeups;
	std::mutex m_mutex;
	std::condition_variable m_condition;

};
END_OGS_NAMESPACE