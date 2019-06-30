#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

#include "task3/tools/i_mutex.h"

namespace qrator_labs
{

namespace tools
{

class Mutex final: public IMutex
{
	pthread_mutex_t				m_mutex;
	bool						m_is_init;

public:
	Mutex();
	~Mutex() override;
	// IMutex interface
public:
	void Lock() override;
	void Unlock() override;
	virtual bool IsValid() const;
};

} // tools

} // qrator_labs

#endif // MUTEX_H
