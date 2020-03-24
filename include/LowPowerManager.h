#ifndef __LOW_POWER_MANAGER_H__
#define __LOW_POWER_MANAGER_H__

/**
 * 
 */
namespace VoyagerAuto{

class WakeLock;
class SysSuspend;

class LowPowerManager {
    LowPowerManager();
public:
    virtual ~LowPowerManager();
    static LowPowerManager& GetInstance();

////////////// wake lock /////////////
	int VA_Lock();				//return lockId ,If < 0, error code
	int VA_Unlock(int lockId);
////////////// sleep /////////////////
	int VA_Sleep(unsigned int sec);
////////////// system suspend ////////////
	int VA_Suspend();
private:
	WakeLock* m_wakeLock;
	SysSuspend* m_sysSuspend;
};

}

#endif
