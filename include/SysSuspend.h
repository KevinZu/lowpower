#ifndef __SYS_SUSPEND_H__
#define __SYS_SUSPEND_H__

#include <vector>
#include <string>

#define   STATE_MEM_NOT_EXIST  -1110

namespace VoyagerAuto {

class SysSuspend {
	SysSuspend();
public:
	virtual ~SysSuspend();

	static SysSuspend& GetInstance();

	int Suspend();
private:
	std::vector<std::string> m_states;
};

}

#endif
