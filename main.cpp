#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "LowPowerManager.h"

using namespace VoyagerAuto;


int main(int argc, char *argv[])
{
	LowPowerManager &manager = LowPowerManager::GetInstance();

	std::cout << "==== lock id: " << manager.VA_Lock() << std::endl;

	manager.VA_Policy();

	manager.VA_Standby();
	
	return 0;
}
