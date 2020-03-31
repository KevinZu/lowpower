#include <iostream>
#include "WakeLock.h"

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

using namespace VoyagerAuto;
using namespace std;
//////////////////////////////////////////////////////////

const char * const NEW_PATHS[] = {
	"/sys/power/wake_lock",
	"/sys/power/wake_unlock",
};


#define MY_ID  "ag35lock"




int	WakeLock::AcquireWakeLock()
{
	int fd;
	fd = m_fds[ACQUIRE_PARTIAL_WAKE_LOCK];
	return write(fd, m_id.c_str(), strlen(m_id.c_str()));
}
int WakeLock::ReleaseWakeLock()
{
	ssize_t len = write(m_fds[RELEASE_WAKE_LOCK], m_id.c_str(), strlen(m_id.c_str()));
	return len >= 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WakeLock::WakeLock() : m_id(MY_ID),m_lock_count(0)
{
	cout << "+ wake lock  my_id:" << m_id << endl;
	int i;
	for (i=0; i<OUR_FD_COUNT; i++) {
		int fd = open(NEW_PATHS[i], O_RDWR | O_CLOEXEC);
		if (fd < 0) {
			printf("fatal error opening \"%s\"\n", NEW_PATHS[i]);
		}
		m_fds[i] = fd;
	}

	
}

WakeLock::~WakeLock()
{
	cout << "- wake lock\n";
	int i;
	for (i=0; i<OUR_FD_COUNT; i++) {
		if(m_fds[i] > 0)
			close(m_fds[i]);
	}
}

WakeLock& WakeLock::GetInstance()
{
	static WakeLock instance_;
	return instance_;
}


int WakeLock::Lock()
{
	if(m_lock_count < 0) {
		cout << "sys lock is failure!" << endl;
		return -1;
	}
	
	if(m_lock_count == 0) {
		AcquireWakeLock();
	}

	m_lock_count += 1;
	
	return m_lock_count;
}


int WakeLock::UnLock(int lockId)
{
	if (m_lock_count <= 0) {
		cout << "lock is already releaseWakeLock!" << endl;
		return -1;
	}
	
	if (m_lock_count == 1) {
		ReleaseWakeLock();
	}

	m_lock_count -= 1;
	
	return m_lock_count;
}

