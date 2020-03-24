#include <iostream>
#include <string>
#include <stdlib.h>
#include "utils.h"
#include "SysSuspend.h"

using namespace VoyagerAuto;
using namespace std;



SysSuspend::SysSuspend()
{
	string powerStates = getCmdResult("cat /sys/power/state");
	m_states = split(powerStates," ");
	for(vector<string>::size_type i = 0;i != m_states.size();++i)
		cout << "power state: " << m_states[i] << endl;
}

SysSuspend::~SysSuspend()
{

}

SysSuspend& SysSuspend::GetInstance()
{
	static SysSuspend instance_;
	return instance_;
}

int SysSuspend::Standby()
{
	for(vector<string>::size_type i = 0;i != m_states.size();++i){
		if (m_states[i] == "mem" ) {
			string cmd = "echo mem > /sys/power/state";
			return system(cmd.c_str());
		}
	}

	cout << "The /sys/power/state dose not have this field" << endl;
	return STATE_MEM_NOT_EXIST;
}



