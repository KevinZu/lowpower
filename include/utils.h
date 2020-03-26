#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>


std::string getCmdResult(const std::string &strCmd);
std::vector<std::string> split(std::string str,std::string pattern);
int usleep_signal_safe(useconds_t usec);


#endif
