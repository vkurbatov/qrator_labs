#ifndef I_THREAD_H
#define I_THREAD_H

#include "task3/tools/i_worker.h"

namespace qrator_labs
{

namespace tools
{

class IThread
{
public:
	virtual ~IThread() {}

public:
	virtual bool IsRunning() const = 0;
	virtual bool Start(IWorker& worker) = 0;
	virtual bool Join() = 0;
};

} // tools

} // qrator_labs


#endif // I_THREAD_H
