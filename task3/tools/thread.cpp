#include "task3/tools/thread.h"


namespace qrator_labs
{

namespace tools
{

void* thread_proc(void* context)
{
	thread_result_t result = 0;

	Thread*	thread = reinterpret_cast<Thread*>(context);

	if (thread->IsRunning() && thread->m_acvive_worker.CanExecute())
	{
		result = thread->m_acvive_worker.Execute();
	}

	thread->m_is_running = false;

	return reinterpret_cast<void*>(result);
}

Thread::Thread(IWorker& worker)
	: m_acvive_worker(worker)
	, m_is_running(false)
	, m_thread_id(0)
	, m_joinable(false)
{

}

Thread::~Thread()
{
	Join();
}

const IWorker &Thread::GetActiveWorker() const
{
	return m_acvive_worker;
}

bool Thread::IsRunning() const
{
	return m_is_running;
}

bool Thread::Start()
{
	return m_joinable ? false : create_thread();
}

bool Thread::Join()
{
	if (m_joinable)
	{
		pthread_join(m_thread_id, nullptr);
		m_joinable = false;
		m_is_running = false;
		return true;
	}
	return false;
}

bool Thread::Joinable() const
{
	return m_joinable;
}

bool Thread::create_thread()
{

	bool result = false;
	pthread_attr_t	thread_attribute;

	pthread_attr_init(&thread_attribute);

	m_is_running = true;

	result = pthread_create(&m_thread_id, &thread_attribute, thread_proc, this) >= 0;

	result &= m_thread_id > 0;

	m_joinable = result;

	return result;
}


} // tools

} // qrator_labs
