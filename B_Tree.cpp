//Author: Zihao Zhang
//Date: 11.26
#include <cstdlib>
#include <iostream>
#include <string>

#include "B_Tree.h"
#include "userInfo.h"

using namespace std;

	treeNode::treeNode(){
		perms = new int[3];
		nodeChildren = new nodeChildren[4];
		leafChildren = new leafChildren[4];
	}

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
			treeLeaf* dest = find_leaf_by_index(user.get_perm(), rootNode);				
			if(dest->isFull == false){						
				dest->userTwo = new userInfo(user);
			}else{

			}




		}
	}



























	void B_Tree::find_leaf_by_index(userInfo user, treeNode* root){				

		int perm = user.get_perm();

		if(root->isAboveLeaf == true){					// at the level of node that above leaves; base case

			if(root->indexUsed == 1){						// if there is only one index available, which means this node has 2 children leaves

				if( perm < root->perms[0]){						// if perm we want to insert is smaller than this index, we go to the right pointer (smaller side)

					if(root->leafChildren[0]->isLeafFull == false){			// go to the correct leaf, if it is not full, just insert

						root->leafChildren[0]->insert(user);

					}else{													// if the correct leaf is full
						if(perm > root->leafChildren[0]->getLargerPerm()){				// the case that perm we want to insert is greater than the larger perm of the leaf

							root->leafChildren[2] = root->leafChildren[1];				// allocate a new leaf for the perm

							root->leafChildren[1] = new treeLeaf(user);

							root->perm[0] = perm;										// adjust index

							root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						}else if(perm < root->leafChildren[0]->getLargerPerm() && perm > root->leafChildren[0]->getSmallerPerm()){				// the case that perm is in between of the largerer and smaller user perms

							root->leafChildren[2] = root->leafChildren[1];																		// push the exsiting larger user to a new leaf

							root->leafChildren[1] = new treeLeaf(*(root->leafChildren[0]->userTwo));

							root->leafChildren[0]->userTwo = new userInfo(user);

							root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

							root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						}else if(perm < root->leafChildren[0]->getSmallerPerm()){																// the case that perm is smaller than the smaller user perm

							root->leafChildren[2] = root->leafChildren[1];																		// allocate a new leaf on the left for the perm

							root->leafChildren[1] = root->leafChildren[0];

							root->leafChildren[0] = new treeLeaf(user);

							root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

							root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						}
					}
				}else if( perm > root->perms[0]){

					if(root->leafChildren[1]->isLeafFull == false){				// go to the correct leaf, if it is not full, just insert

						root->leafChildren[1]->insert(user);

					}else{														//if the correct leaf is full
						
						if(perm < root->leafChildren[1]->getLargerPerm()){

						}else if(perm > root->leafChildren[1]->getLargerPerm()){

						}

					}
					

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





