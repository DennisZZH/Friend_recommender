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

	treeNode(const treeNode& copy);

	int perms[];
	treeNode* nodeChildren[];
	treeLeaf* leafChildren[];
	bool isAboveLeaf = true;
	bool isNodeFull = false;
	int indexUsed = 0;
	int GraphIndex = 0; //index of the node userInfo object in the relation graph adjacency list

	treeNode* parent = NULL;
};

struct treeLeaf{

	treeLeaf();

	treeLeaf(userInfo user);			// invariant: userone must always be smaller than usertwo

	treeLeaf(const treeLeaf& copy);

	void insert(userInfo user);

	int getSmallerPerm();						// return the smaller perm

	int getLargerPerm();						// return the larger perm

	userInfo* userOne;
	userInfo* userTwo;
	bool isLeafFull = false;

};

public:

	B_Tree();		// constructor

	void add_user(userInfo user, int index);    //The index of the node userInfo object in the relation graph adjacency list

	bool find_user(int perm);

	void find_and_insert(int perm, treeNode* root);

	void break_up(treeNode* current);

	int get_node_index(treeNode* current);

	int get_graph_index(int perm);

	userInfo get_userInfo(int perm);

private:
	
	treeNode* rootNode;

	treeLeaf* rootLeaf;

	bool isOnlyLeaf;

};
#endif