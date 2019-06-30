#ifndef TOOLS_THREAD_H
#define TOOLS_THREAD_H

#include "task3/tools/i_thread.h"


#include <pthread.h>

namespace qrator_labs
{

namespace tools
{

class Thread : public virtual IThread
{
	IWorker&			m_acvive_worker;
	volatile bool		m_is_running;
	volatile bool		m_joinable;
	pthread_t			m_thread_id;

public:
	Thread(IWorker& worker);
	virtual ~Thread();

public:
	// IThread interface
	const IWorker& GetActiveWorker() const override;
	bool IsRunning() const override;
	bool Start() override;
	bool Join() override;
	bool Joinable() const;

private:
	bool create_thread();

	friend void* thread_proc(void* context);
};

} // tools

} // qrator_labs

#endif // THREAD_H
