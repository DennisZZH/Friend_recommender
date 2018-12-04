//Author: Zihao Zhang
//Date: 11.25
#ifndef TREENODE
#define TREENODE

#include <cstdlib>
#include <iostream>
#include <string>

#include "B_Tree.h"
#include "userInfo.h"
#include "treeLeaf.h"

using namespace std;

class treeLeaf; 

class treeNode{ 

public:

	treeNode();

	int* perms;
	treeNode** nodeChildren;
	treeLeaf** leafChildren;
	bool isAboveLeaf;
	bool isNodeFull;
	int indexUsed;

	treeNode* parent;

private:

};
#endif