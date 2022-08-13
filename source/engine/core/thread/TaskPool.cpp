#include "TaskPool.h"
#include "Task.h"
#include <chrono>
#include <iostream>

BEGIN_OGS_NAMESPACE

#define SLEEP(ms)			std::this_thread::sleep_for((std::chrono::milliseconds(ms)))
#define LOCK_GUARD( lock )	std::lock_guard<std::mutex> lockguard(lock)

std::mutex print;

void TaskPool::threadFunc(TaskPool* pool)
{
	Task* curtask = nullptr;
	std::thread::id curid = std::this_thread::get_id();

	do
	{
		{
			curtask = nullptr;
			LOCK_GUARD(pool->m_tasklock);
			if (pool->m_taskqueue.size() > 0)
			{
				curtask = pool->m_taskqueue.front();
				pool->m_taskqueue.pop();
			}
		}

		if (curtask != nullptr)
		{
			curtask->doJob();
			SAFE_DELTE(curtask);
		}
		else
		{
			pool->m_signal.wait();
		}
	} while (!pool->m_quit);
}

TaskPool::TaskPool()
{

}

TaskPool::~TaskPool()
{
	m_quit = true;
	for (auto it = m_threads.begin(); it != m_threads.end(); it++)
	{
		(*it).detach();
	}
	m_threads.clear();
}

void TaskPool::addTask(Task* task)
{
	if (task == nullptr) return;

	{
		LOCK_GUARD(m_tasklock);
		m_taskqueue.push(task);
	}

	{
		LOCK_GUARD(print);
		std::cout << " add task" << std::endl;
	}

	m_signal.signalAll();
}

bool TaskPool::init()
{
	int	threadnum = std::max(std::thread::hardware_concurrency(), (unsigned int)1);
	
	m_threads.resize(threadnum);

	for (int i = 0; i < threadnum; i++)
	{
		m_threads.push_back(std::thread(TaskPool::threadFunc, this));
	}

	return true;
}



END_OGS_NAMESPACE