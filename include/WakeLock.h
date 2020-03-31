#ifndef __WAKE_LOCK_H__
#define __WAKE_LOCK_H__

#include <stdint.h>
#include <string>


namespace VoyagerAuto {

enum {
	ACQUIRE_PARTIAL_WAKE_LOCK = 0,
	RELEASE_WAKE_LOCK,
	OUR_FD_COUNT
};

enum {
	PARTIAL_WAKE_LOCK = 1,  // the cpu stays on, but the screen is off
	FULL_WAKE_LOCK = 2      // the screen is also on
};

#if __cplusplus
extern "C" {
#endif

// while you have a lock held, the device will stay on at least at the
// level you request.
int acquire_wake_lock(int lock, const char* id);
int release_wake_lock(const char* id);
#if __cplusplus
} // extern "C"
#endif

class WakeLock {
	WakeLock();
public:
	virtual ~WakeLock();
	static WakeLock& GetInstance();

	int Lock();
	int UnLock(int);
private:
	int AcquireWakeLock();
	int ReleaseWakeLock();
	int m_fds[OUR_FD_COUNT];
	std::string m_id;
	int m_lock_count;
};

}

#endif

