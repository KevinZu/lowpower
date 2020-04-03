#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"
#include "SysSuspend.h"

using namespace nebula;
using namespace std;



SysSuspend::SysSuspend()
{
	m_stateFd = open("/sys/power/state", O_WRONLY, O_CLOEXEC);
	if (m_stateFd == -1) {
		perror("Error opening power state");
	}
	string powerStates = getCmdResult("cat /sys/power/state");
	m_states = split(powerStates," ");
	for(vector<string>::size_type i = 0;i != m_states.size();++i) {
		cout << "power state: " << m_states[i] << endl;
	}
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

int SysSuspend::AutoSleepEnable()
{
	for(vector<string>::size_type i = 0;i != m_states.size();++i){
		if (m_states[i] == "mem" ) {
			string cmd = "echo mem > /sys/power/autosleep";
			cout << cmd << endl;
			return system(cmd.c_str());
		}
	}

	cout << "The /sys/power/state dose not have this field" << endl;
	return STATE_MEM_NOT_EXIST;
}

int SysSuspend::Suspend()
{
	int rc = 0;

	if(m_stateFd == -1){
		cout << "m_stateFd == -1" << endl;
		return -1;
	}
	
	rc = TEMP_FAILURE_RETRY(write(m_stateFd, "mem", 3));
	if (rc == -1) {
		if (errno == EBUSY) {
			/* EBUSY is acceptable */
			rc = -errno;
		} else {
			perror("Failed to write to power state file");
			exit(1);
		}
	} else {
		rc = 0;
	}
	return rc;
}




