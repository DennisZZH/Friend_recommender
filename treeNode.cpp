//Author: Zihao Zhang
//Date: 11.26
#include <cstdlib>
#include <iostream>
#include <string>

#include "treeNode.h"

using namespace std;

treeNode::treeNode(){

	perms = new int[3];

	for(int i = 0; i < 3; i ++){
			perms[i] = 0;
	}

	nodeChildren = new treeNode*[4];

	leafChildren = new treeLeaf*[4];
		
	isAboveLeaf = true;

	isNodeFull = false;

	indexUsed = 0;

	parent = NULL;

}