#ifndef I_MUTEX_H
#define I_MUTEX_H

namespace qrator_labs
{

namespace tools
{

class IMutex
{
public:
	virtual ~IMutex() {}
	virtual void Lock() = 0;
	virtual void Unlock() = 0;
	virtual bool IsValid() const = 0;
};

} // tools

} // qrator_labs

#endif // I_MITEX_H
