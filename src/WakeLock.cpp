#include <iostream>
#include "WakeLock.h"

using namespace VoyagerAuto;
using namespace std;
//////////////////////////////////////////////////////////

WakeLock::WakeLock()
{
	cout << "+ wake lock\n";
}

WakeLock::~WakeLock()
{
	cout << "- wake lock\n";
}

WakeLock& WakeLock::GetInstance()
{
	static WakeLock instance_;
	return instance_;
}


int WakeLock::Lock()
{
	return 0;
}


int WakeLock::UnLock(int lockId)
{
	return 0;
}

