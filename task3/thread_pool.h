#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "task3/tools/thread.h"
#include "task3/tools/mutex.h"
#include <array>
#include <queue>
#include <vector>

namespace qrator_labs
{

class ThreadPool
{
public:
	enum thread_priority_t
	{
		low,
		normal,
		high
	};

private:

	class PoolWorker : public tools::IWorker
	{
		ThreadPool&		m_owner_thread_pool;

	public:
		PoolWorker(ThreadPool& owner_pool);

		// IWorker interface
	public:
		tools::thread_result_t Execute() override;
		bool CanExecute() const override;
	};

	static const std::int32_t worker_queue_count = static_cast<std::size_t>(thread_priority_t::high) + 1;

	typedef std::queue<tools::IWorker*> worker_queue_t;
	typedef std::array<worker_queue_t, worker_queue_count> task_queue_t;
	typedef std::vector<tools::Thread> thread_pool_t;

private:

	tools::Mutex		m_queue_mutex;
	task_queue_t		m_task_queue;
	PoolWorker			m_pool_worker;
	volatile bool		m_is_stop;

	std::uint32_t		m_high_task_counter;

	thread_pool_t		m_pool;

public:
	ThreadPool(std::size_t pool_size);
	~ThreadPool();

	bool Enqueue(tools::IWorker* worker, thread_priority_t priority);
	bool Stop();
	void Wait();

private:

	tools::IWorker*		fetch_worker(thread_priority_t& priority);
	thread_priority_t	get_next_order_priority();
	tools::IThread*		get_free_task();
	void				clear_task_queue();
	void				wait_all_tasks();
};

}
#endif // THREAD_POOL_H
