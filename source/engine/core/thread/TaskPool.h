#pragma once

#include "common.h"
#include "core/tool/Singleton.h"
#include "Semaphore.h"

#include <unordered_map>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
BEGIN_OGS_NAMESPACE

class Task;

class TaskPool final : public Singleton<TaskPool>
{
public:
	typedef std::queue<Task*> TaskQueue;
public:
	TaskPool();
	virtual ~TaskPool();

	void addTask(Task* task);
private:
	virtual bool init()override;
	static void threadFunc(TaskPool* pool);
private:
	std::mutex m_tasklock;
	TaskQueue m_taskqueue;
	std::vector<std::thread> m_threads;
	Semaphore m_signal;
	bool m_quit = false;
};
END_OGS_NAMESPACE