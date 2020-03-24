#ifndef __WAKE_LOCK_H__
#define __WAKE_LOCK_H__

namespace VoyagerAuto {

class WakeLock {
	WakeLock();
public:
	virtual ~WakeLock();
	static WakeLock& GetInstance();

	int Lock();
	int UnLock(int);
};

}

#endif

