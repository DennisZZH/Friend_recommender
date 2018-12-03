//Author: Zihao Zhang
//Date: 11.25
#ifndef USERINFO_H
#define USERINFO_H

#include <cstdlib>
#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class userInfo{

public:

	userInfo() = default;

	userInfo(int perm, string name, string genre1, string genre2, int index);	// constructor

	userInfo(userInfo &newUser);

	const int get_perm(){ return userObject->get_perm();}			// getter functions
	const string get_name(){ return userObject->get_name();}
	const string get_genre1(){ return userObject->get_genre1();}
	const string get_genre2(){ return userObject->get_genre2();}
	const int get_graph_index(){ return GraphIndex;}

private:
	user* userObject;
	int GraphIndex = 0;

};
#endif