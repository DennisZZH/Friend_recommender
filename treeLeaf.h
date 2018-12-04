//Author: Zihao Zhang
//Date: 11.25
#ifndef TREELEAF
#define TREELEAF

#include <cstdlib>
#include <iostream>
#include <string>

#include "B_Tree.h"
#include "userInfo.h"
#include "treeNode.h"

using namespace std;

class treeLeaf{

public:

	treeLeaf(userInfo user);			// invariant: userone must always be smaller than usertwo

	void insert(userInfo user);

	int getSmallerPerm();						// return the smaller perm

	int getLargerPerm();						// return the larger perm

	userInfo* userOne;

	userInfo* userTwo;

	bool isLeafFull = false;

private:

};
#endif