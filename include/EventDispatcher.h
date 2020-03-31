#ifndef __EVENT_DISPATCHER_H__
#define __EVENT_DISPATCHER_H__

#include "WakeLock.h"

namespace VoyagerAuto {

//class WakeLock;

class EventDispatcher {
	EventDispatcher();
public:
	virtual ~EventDispatcher();

	static EventDispatcher& GetInstance();

	void SetWakeLock(WakeLock *wl);
	WakeLock *GetWakeLock(){return m_wakeLock;}

	int GetWakeIntLock(){return m_wakeIntLock;}
	void SetWakeIntLock(int lockId){m_wakeIntLock = lockId;}
private:
	WakeLock* m_wakeLock;
	int m_wakeIntLock;
};

}

#endif

