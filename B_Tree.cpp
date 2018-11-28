//Author: Zihao Zhang
//Date: 11.26
#include <cstdlib>
#include <iostream>
#include <string>

#include "B_Tree.h"
#include "userInfo.h"

using namespace std;

	B_Tree::B_Tree(){
		this->rootNode = NULL;
		this->rootLeaf = NULL;
		this->isOnlyLeaf = true;
	}

	void B_Tree::add_user(userInfo user){
		if(isOnlyLeaf == true){								// in the case that there are only leaves.
			if(rootLeaf == NULL){							// 1st insertion, root points to a leaf
				rootLeaf = new treeLeaf();
				rootLeaf->userOne = new userInfo(user);
			}else if(rootLeaf != NULL && rootLeaf->isFull != true){						// second insertion, leaf full
				if(user.get_perm() > rootLeaf->userOne->get_perm()){					// make sure perm number of userOne is always < perm number of userTwo
					rootLeaf->userTwo = new userInfo(user);
				}else{
					rootLeaf->userTwo = rootLeaf->userOne;
					rootLeaf->userOne = new userInfo(user);
				}
				rootLeaf->isFull = true;
			}else if(rootLeaf != NULL && rootLeaf->isFull == true){			// third insertion, object number exceed leaf size by 1, need to use treeNode now
				rootNode = new treeNode();
				if(user.get_perm() < rootLeaf->userOne->get_perm()){		// third user's perm is the smallest
					rootNode->leafChildren[0] = new treeLeaf();
					rootNode->leafChildren[0]->userOne = new userInfo(user);
					rootNode->leafChildren[1] = rootLeaf;
					rootNode->perms[0] = leafChildren[1]->userOne->get_perm();
					rootNode->indexUsed++;
				}else if(user.get_perm() > rootLeaf->userTwo->get_perm()){				// third user's perm is the greatest
					rootNode->leafChildren[1] = new treeLeaf();
					rootNode->leafChildren[1]->userOne = new userInfo(user);
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->perms[0] = leafChildren[1]->userOne->get_perm();
					rootNode->indexUsed++;												// third user's perm is in between of the first and second
				}else{
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->leafChildren[1] = new treeLeaf();
					rootNode->leafChildren[1]->userOne = rootNode->leafChildren[0]->userTwo;		// rearrange, place the smaller two user on the first leaf, largest one user on the second leaf
					rootNode->leafChildren[0]->userTwo = new userInfo(user);
					rootNode->perms[0] = leafChildren[1]->userOne->get_perm();	
					rootNode->indexUsed++;
				}
				isOnlyLeaf = false;
				rootLeaf = NULL;
			}
		}
		else if( isOnlyLeaf == false){
			treeLeaf* dest = find_leaf_by_index(user.get_perm(), rootNode);				// find the place this user belong to
			if(dest->isFull == false){						// if there is place available, put it in
				dest->userTwo = new userInfo(user);
			}else{}




		}
	}



	treeLeaf* B_Tree::find_leaf_by_index(int perm, treeNode* root){				// given a root ptr and a perm, find the appropriate leaf that the perm should be in

		if(root->isAboveLeaf == true){					// base case: when root is the ptr to a node just above leaf
			if(root->indexUsed == 1){
				if(perm < root->perms[0]){
					return root->leafChildren[0];
				}else{
					return root->leafChildren[1];
				}
			}else if(root->indexUsed == 2){
				if(perm < root->perms[0]){
					return root->leafChildren[0];
				}else if(perm >= perms[0] && perm < perms[1]){
					return root->leafChildren[1];
				}else{
					return root->leafChildren[2];
				}
			}else if(root->indexUsed == 3){
				if(perm < root->perms[0]){
					return root->leafChildren[0];
				}else if(perm >= perms[0] && perm < perms[1]){
					return root->leafChildren[1];
				}else if(perm >= perms[1] && perm < perms[2]){
					return root->leafChildren[2];
				}else{
					return root->leafChildren[3];
				}
			}
		}else{

			if(perm < root->perms[0]){
				return find_leaf_by_index(perm, root->nodeChildren[0]);
			}else if(perm > root->perms[indexUsed - 1]){
				return find_leaf_by_index(perm, root->nodeChildren[indexUsed]);
			}else if(indexUsed == 2){
				if(perm >= root->perms[0] && perm < root->perms[1]){
					return find_leaf_by_index(perm, root->nodeChildren[1]);
				}
			}else if(index == 3){
				if(perm >= root->perms[0] && perm < root->perms[1]){
					return find_leaf_by_index(perm, root->nodeChildren[1]);
				}else if(perm >= perms[1] && perm < perms[2]){
					return find_leaf_by_index(perm, root->nodeChildren[2]);
				}
			}															
		}
																				
	}





