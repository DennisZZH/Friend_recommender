//Author: Zihao Zhang
//Date: 11.25

#ifndef B_TREE
#define B_TREE

#include <cstdlib>
#include <iostream>
#include <string>

#include "userInfo.h"

using namespace std;

class userInfo;

class B_Tree{

struct treeNode{
	struct treeLeaf; 

	treeNode();

	int perms[];
	treeNode* nodeChildren[];
	treeLeaf* leafChildren[];
	bool isAboveLeaf = true;
	bool isNodeFull = false;
	int indexUsed = 0;

	treeNode* parent = NULL;
};

struct treeLeaf{

	treeLeaf();

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

	void add_user(userInfo user);   // general add function

	bool find_user(int perm);

	void find_and_insert(userInfo user, treeNode* root);  // add function, under the condition that isOnlyLeaf is false ( after third insertion)

	void break_up(treeNode* current);				// general break up funtion, used when a node of a leaf is full and need to be broken down

	void break_when_parent_not_full(treeNode* current)	// break function, under the condition that the current node's parent is not full, thus just break the current node, and reallocate its siblings

	int get_node_index(treeNode* current);			// given a treeNode pointer, find the smaller perm of left most leaf under that treeNode.(find the smallest perm under that node) 

	userInfo get_userInfo(int perm);

private:
	
	treeNode* rootNode;

	treeLeaf* rootLeaf;

	bool isOnlyLeaf;

};
#endif