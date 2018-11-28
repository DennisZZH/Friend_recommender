//Author: Zihao Zhang
//Date: 11.25
#ifndef USERINFO_H
#define USERINFO_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class userInfo{

public:

	userInfo();		// default constructor

	userInfo(int perm, string name, string genre1, string genre2);	// constructor

	int get_perm(){ return perm;};			// getter functions
	string get_name(){ return name;};
	string get_genre1(){ return genre1;};
	string get_genre2(){ return genre2;};

private:
	int perm ; // unique id
	string name ; // name of the person
	string genre1 ; // first favorite movie genre
	string genre2 ; // second favorite movie genre
};
#endif