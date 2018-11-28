//Author: Zihao Zhang
//Date: 11.25
#ifndef BTREE.H
#define BTREE.H

#include <cstdlib>
#include <iostream>
#include <string>

#include "userInfo.h"

using namespace std;

class userInfo;

class B_Tree{

struct treeNode{
	treeNode(){
		perms = new int[3];
		nodeChildren = new nodeChildren[4];
		leafChildren = new leafChildren[4];
	}
	int perms[];
	treeNode* nodeChildren[];
	treeLeaf* leafChildren[];
	bool isAboveLeaf = true;
	bool isNodeFull = false;
	int indexUsed = 0;
};

struct treeLeaf{
	userInfo* userOne;
	userInfo* userTwo;
	bool isLeafFull = false;
};

public:

	B_Tree();		// constructor

	void add_user(userInfo user);

	bool find_user(int perm);

	const treeLeaf* find_leaf_by_index(int perm, treeNode* root);

private:
	
	treeNode* rootNode;

	treeLeaf* rootLeaf;

	bool isOnlyLeaf;

};
#endif





















