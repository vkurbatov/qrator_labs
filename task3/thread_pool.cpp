/*
	Задача 3 (ThreadPool)
	Реализовать ThreadPool:

	• при создании указывается один параметр - число воркеров, которые будут выполнять задачи.

	◦ метод Enqueue имеет два параметра - объект(ссылку на объект), описывающий задачу, которую
	надо будет выполнить (например абстрактного типа с методом .do()) и приоритет(пусть всего
	будет три приоритета - low, normal, high).

	◦ метод Stop() - ожидает завершения выполняемых (в данный момент) задач, после чего убивает
	воркеры и возвращает управление.

	• Enqueue добавляет задачи в очередь на выполнение и возвращает true (если до этого не был
	вызван Stop - в этом случае Enqueue возвращает false).
	• Приоритеты обрабатываются следующим образом:

	◦ low-задачи не выполняются никогда, пока в очереди есть хотя бы одна задача с другим приоритетом.

	◦ на 3 high-задачи выполняется 1 normal-задача.

	◦ Данная логика относится только к выборке задачи из очереди, уже запущенные задачи приоритизировать
	не требуется.
*/

#include "thread_pool.h"

namespace qrator_labs
{

ThreadPool::ThreadPool(std::size_t pool_size)
	: m_pool_worker(*this)
	, m_is_stop(false)
	, m_high_task_counter(0)
{
	while (pool_size-- > 0)
	{
		m_pool.push_back(tools::Thread(m_pool_worker));
	}
}

ThreadPool::~ThreadPool()
{
	Stop();
}

bool ThreadPool::Enqueue(tools::IWorker *worker, ThreadPool::thread_priority_t priority)
{
	if (m_is_stop == false && worker != nullptr)
	{
		m_queue_mutex.Lock();

		m_task_queue[priority].push(worker);

		m_queue_mutex.Unlock();

		tools::IThread* free_task = get_free_task();

		if (free_task != nullptr)
		{
			if (free_task->Joinable())
			{
				free_task->Join();
			}
			free_task->Start();
		}

		return true;
	}

	return false;
}

bool ThreadPool::Stop()
{
	if (m_is_stop == false)
	{
		m_is_stop = true;

		wait_all_tasks();

		m_queue_mutex.Lock();

		clear_task_queue();

		m_queue_mutex.Unlock();

		return true;
	}

	return false;
}

void ThreadPool::Wait()
{
	wait_all_tasks();
}

tools::IWorker* ThreadPool::fetch_worker(thread_priority_t& priority)
{
	tools::IWorker* result = nullptr;

	m_queue_mutex.Lock();

	priority = get_next_order_priority();

	if (m_task_queue[priority].size() > 0)
	{
		result = m_task_queue[priority].front();
		m_task_queue[priority].pop();
	}
	else
	{
		priority = priority;
	}

	m_queue_mutex.Unlock();

	return result;
}

ThreadPool::thread_priority_t ThreadPool::get_next_order_priority()
{
	thread_priority_t result = thread_priority_t::high;

	std::size_t high_task_count = m_task_queue[thread_priority_t::high].size();
	std::size_t normal_task_count = m_task_queue[thread_priority_t::normal].size();

	if (high_task_count > 0)
	{
		if (m_high_task_counter > 0 && normal_task_count > 0)
		{
			if (normal_task_count > 0)
			{
				result = thread_priority_t::normal;
			}
		}
	}
	else if (normal_task_count > 0)
	{
		result = thread_priority_t::normal;
	}
	else
	{
		result = thread_priority_t::low;
	}

	return result;
}

tools::IThread* ThreadPool::get_free_task()
{
	for (thread_pool_t::iterator it = m_pool.begin();
		 it != m_pool.end();
		 it++)
	{
		if ((*it).IsRunning() == false)
		{
			return &(*it);
		}
	}

	return nullptr;
}

void ThreadPool::clear_task_queue()
{
	for (std::uint32_t queue_number = 0; queue_number < worker_queue_count; queue_number++)
	{
		worker_queue_t& queue = m_task_queue[queue_number];

		while(!queue.empty())
		{
			tools::IWorker* worker = queue.front();
			queue.pop();

			if(worker != nullptr)
			{
				delete worker;
			}
		}
	}
}

void ThreadPool::wait_all_tasks()
{
	for (std::vector<tools::Thread>::iterator it = m_pool.begin(); it != m_pool.end(); it++)
	{
		if ((*it).Joinable())
		{
			(*it).Join();
		}
	}
}


// -------------------------------------------------------------------

ThreadPool::PoolWorker::PoolWorker(ThreadPool &owner_pool)
	: m_owner_thread_pool(owner_pool)
{

}

tools::thread_result_t ThreadPool::PoolWorker::Execute()
{
	while(CanExecute())
	{
		thread_priority_t priority;
		IWorker* worker = m_owner_thread_pool.fetch_worker(priority);

		if (worker != nullptr)
		{
			if (priority == thread_priority_t::high)
			{
				m_owner_thread_pool.m_high_task_counter++;
			}
			else
			{
				m_owner_thread_pool.m_high_task_counter = 0;
			}
			worker->Execute();
			delete worker;
		}
		else
		{
			break;
		}
	}

	return 0;
}

bool ThreadPool::PoolWorker::CanExecute() const
{
	return m_owner_thread_pool.m_is_stop == false;
}


} // qrator_labs
