//Author: Zihao Zhang
//Date: 11.25

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

	void add_user(userInfo user);

	bool find_user(int perm);

	void find_and_insert(int perm, treeNode* root);

	void break_up(treeNode* current);

	int get_node_index(treeNode* current);

private:
	
	treeNode* rootNode;

	treeLeaf* rootLeaf;

	bool isOnlyLeaf;

};