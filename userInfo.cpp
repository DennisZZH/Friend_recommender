//Author: Zihao Zhang
//Date: 11.25.2018
#include <iostream>
#include <cstdlib>
#include <string>

#include "userInfo.h"

userInfo::userInfo(int perm, std::string name, std::string genre1, std::string genre2, int index) {
	userObject = new user(perm, name, genre1, genre2);
	GraphIndex = index;
}

userInfo::userInfo(userInfo &newUser) {
	userObject = new user(newUser.get_perm(), newUser.get_name(), newUser.get_genre1(), newUser.get_genre2());
	GraphIndex = newUser.get_graph_index();
}
