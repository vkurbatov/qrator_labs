#ifndef I_WORKER_H
#define I_WORKER_H

#include "task3/tools/tools_types.h"

namespace qrator_labs
{

namespace tools
{

class IWorker
{

public:
	virtual ~IWorker() {}

public:
	virtual thread_result_t Execute() = 0;
	virtual bool CanExecute() const = 0;
};

} // tools

} // qrator_labs

#endif // I_WORKER_H
