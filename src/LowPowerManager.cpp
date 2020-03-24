#include <iostream>
#include "WakeLock.h"
#include "SysSuspend.h"
#include "LowPowerManager.h"

using namespace std;
using namespace VoyagerAuto;
///////////////////////////////////////////////////// 
///LowPowerManager ////////////////////////////// 


LowPowerManager::LowPowerManager() 
{
	m_wakeLock = &WakeLock::GetInstance();
	m_sysSuspend = &SysSuspend::GetInstance();
	cout << "==========\n";
}


LowPowerManager::~LowPowerManager()
{
	cout << "----------------------\n";
}


LowPowerManager& LowPowerManager::GetInstance()
{
	static LowPowerManager instance_;
	return instance_; 
}

////////////////// wake lock /////////////////
int LowPowerManager::VA_Lock()
{
	return m_wakeLock->Lock();
}

int LowPowerManager::VA_Unlock(int lockId)
{
	return m_wakeLock->UnLock(lockId);
}


//////////////// sleep //////////////////////
int LowPowerManager::VA_Sleep(unsigned int sec)
{
	return 0;
}


/////////////// auto sleep //////////////////
int LowPowerManager::VA_Suspend()
{
	return m_sysSuspend->Suspend();
}

