#ifndef THREAD_H
#define THREAD_H

#include <atomic>
#include "task3/tools/i_thread.h"

#include <pthread.h>

namespace qrator_labs
{

namespace tools
{

class Thread : public virtual IThread
{
	std::atomic_bool	m_is_running;

	pthread_t			m_thread_id;

public:
	Thread();
	Thread(IWorker& worker);
	virtual ~Thread();

public:
	// IThread interface
	bool IsRunning() const override;
	bool Start(IWorker& worker) override;
	bool Join() override;

private:

	pthread_t internal_create_thread(IWorker& worker);

};

} // tools

} // qrator_labs

#endif // THREAD_H
