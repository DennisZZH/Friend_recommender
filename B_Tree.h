//Author: Zihao Zhang
//Date: 11.25

#ifndef B_TREE
#define B_TREE

#include <cstdlib>
#include <iostream>
#include <string>

#include "userInfo.h"
#include "treeNode.h"
#include "treeLeaf.h"

using namespace std;

class userInfo;

class treeNode;

class treeLeaf;

class B_Tree{

public:

	B_Tree();		// constructor

	void add_user(userInfo user);   // general add function

	bool find_user(int perm);

	void find_and_insert(userInfo user, treeNode* root);  // add function, under the condition that isOnlyLeaf is false ( after third insertion)

	void break_up(treeNode* current);				// general break up funtion, used when a node of a leaf is full and need to be broken down

	void break_when_parent_not_full(treeNode* current);	// break function, under the condition that the current node's parent is not full, thus just break the current node, and reallocate its siblings

	int get_node_index(treeNode* current);			// given a treeNode pointer, find the smaller perm of left most leaf under that treeNode.(find the smallest perm under that node) 

	userInfo get_userInfo(int perm);

private:
	
	treeNode* rootNode;

	treeLeaf* rootLeaf;

	bool isOnlyLeaf;

};
#endif