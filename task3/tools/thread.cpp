#include "task3/tools/thread.h"

namespace qrator_labs
{

namespace tools
{

namespace thread_utils
{

}

Thread::Thread()
	: m_thread_id(0)
{
	pthread_t threadl;
}

Thread::Thread(IWorker& worker)
{

}

Thread::~Thread()
{
	Join();

}

bool Thread::IsRunning() const
{
	return false;
}

bool Thread::Start(IWorker& worker)
{

	return false;
}

bool Thread::Join()
{

}

pthread_t Thread::internal_create_thread(IWorker& worker)
{

}

/*Thread::Thread()
{

}

Thread::Thread(IWorker& worker)
{

}*/

} // tools

} // qrator_labs
