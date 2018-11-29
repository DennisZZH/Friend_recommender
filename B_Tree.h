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

	treeNode();

	int perms[];
	treeNode* nodeChildren[];
	treeLeaf* leafChildren[];
	bool isAboveLeaf = true;
	bool isNodeFull = false;
	int indexUsed = 0;
};

struct treeLeaf{

	treeLeaf(userInfo user);			// invariant: userone must always be smaller than usertwo

	void insert(userInfo user);

	int getSmallerPerm();						// return the smaller perm

	int getLargerPerm();						// return the larger perm

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





















