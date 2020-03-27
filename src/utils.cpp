#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

using namespace std;
 
string getCmdResult(const string &strCmd)
{
	char buf[10240] = {0};
	FILE *pf = NULL;
	
	if( (pf = popen(strCmd.c_str(), "r")) == NULL ){
		return "";
	}
 
	string strResult;
	while(fgets(buf, sizeof buf, pf)){
		strResult += buf;
	}
	
	pclose(pf);
 
	unsigned int iSize =  strResult.size();
	if(iSize > 0 && strResult[iSize - 1] == '\n') { // linux
		strResult = strResult.substr(0, iSize - 1);
	}
 
	return strResult;
}


std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;

	str+=pattern;
	int size=str.size();

	for(int i=0; i<size; i++) {
		pos=str.find(pattern,i);
		if(pos<size) {
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	
	return result;
}


