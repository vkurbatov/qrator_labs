#include "tasks.h"
#include "common/common.h"

#include <iostream>

#include "task3/tools/i_worker.h"
#include "task3/tools/thread.h"
#include "task3/tools/mutex.h"

#include "task3/thread_pool.h"

#include <unistd.h> // usleep

namespace qrator_labs
{

namespace task3
{

class WaitWorker : public tools::IWorker
{
	std::string		m_name;
	std::uint32_t	m_wait_ms;

public:
	WaitWorker(const std::string& worker_name, std::uint32_t wait_ms)
		: m_name(worker_name)
		, m_wait_ms(wait_ms)
	{

	}

	// IWorker interface
public:
	tools::thread_result_t Execute() override
	{
		std::cout << "Wait worker {" << m_name << "} begin work [" << m_wait_ms << "ms]" << std::endl;
		usleep(m_wait_ms * 1000);
		std::cout << "Wait worker {" << m_name << "} end work" << std::endl;
	}

	bool CanExecute() const override
	{
		return true;
	}
};

static const std::size_t pool_size = 6;
static const std::size_t task_count = 50;

static const std::uint32_t min_wait = 100;
static const std::uint32_t max_wait = 1000;

std::int32_t test1()
{
	std::cout << "Task 3: ThreadPool demonstration:" << std::endl << std::endl;

	const std::string task_names [] = { "LOW", "NORMAL", "HIGH" };

	ThreadPool	thread_pool(pool_size);

	for (std::uint32_t i = 0; i < task_count; i++)
	{
		ThreadPool::thread_priority_t priority = static_cast<ThreadPool::thread_priority_t>(get_random(ThreadPool::thread_priority_t::low, ThreadPool::thread_priority_t::high));
		thread_pool.Enqueue(new WaitWorker(task_names[priority] + std::to_string(i), get_random(min_wait, max_wait)), priority);
	}

	thread_pool.Wait();

	thread_pool.Stop();

}

} // task1

} // qrator_labs
