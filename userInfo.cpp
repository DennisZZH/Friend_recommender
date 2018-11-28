//Author: Zihao Zhang
//Date: 11.25.2018
#include <iostream>
#include <cstdlib>
#include <string>

#include "userInfo.h"

using namespace std;

	userInfo::userInfo(int perm, string name, string genre1, string genre2){
		this->perm = perm;
		this->name = name;
		this->genre1 = genre1;
		this->genre2 = genre2;
	}
