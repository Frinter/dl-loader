#include <stdexcept>
#include <windows.h>

#include "mutex.hh"

namespace Windows {
    class Mutex : public ::Mutex {
    public:
	Mutex() {
            _inCriticalSection = false;
            InitializeCriticalSection(&_criticalSection);
	}

	virtual ~Mutex() {
            DeleteCriticalSection(&_criticalSection);
	}

	virtual void lock() {
            EnterCriticalSection(&_criticalSection);
            _inCriticalSection = true;
	}

	virtual void unlock() {
            if (_inCriticalSection)
            {
                _inCriticalSection = false;
                LeaveCriticalSection(&_criticalSection);
            }
	}

    private:
	CRITICAL_SECTION _criticalSection;
	bool _inCriticalSection;
    };
}

Mutex *Mutex::create()
{
    return new Windows::Mutex();
}
