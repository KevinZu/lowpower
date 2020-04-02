#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "LowPowerManager.h"

using namespace VoyagerAuto;


int main(int argc, char *argv[])
{
	LowPowerManager &manager = LowPowerManager::GetInstance();

	//std::cout << "==== lock id: " << manager.VA_Lock() << std::endl;

	//manager.VA_Policy();

	//manager.VA_Standby();
	manager.VA_AutoSleepEnable();
	while(1) {
		sleep(10);
	}	
	return 0;
}
