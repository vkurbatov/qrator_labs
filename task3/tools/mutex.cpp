#include "mutex.h"

namespace qrator_labs
{

namespace tools
{

Mutex::Mutex()
	: m_is_init(false)
{
	m_is_init = pthread_mutex_init(&m_mutex, nullptr) >= 0;
}

Mutex::~Mutex()
{
	if (m_is_init)
	{
		pthread_mutex_destroy(&m_mutex);
	}
}

void Mutex::Lock()
{
	if (m_is_init)
	{
		pthread_mutex_lock(&m_mutex);
	}
}

void Mutex::Unlock()
{
	if (m_is_init)
	{
		pthread_mutex_unlock(&m_mutex);
	}
}

bool Mutex::IsValid() const
{
	return m_is_init;
}


} // tools

} // qrator_labs
