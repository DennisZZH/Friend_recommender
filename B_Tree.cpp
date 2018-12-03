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
		if(isOnlyLeaf == true){							// in the case that there are only leaves.
			if(rootLeaf == NULL){							// 1st insertion, root points to a leaf
				rootLeaf = new treeLeaf(user);
			}else if(rootLeaf != NULL && rootLeaf->isFull == false){						// second insertion, leaf full
				rootLeaf->insert(user);
				rootLeaf->isFull = true;
			}else if(rootLeaf != NULL && rootLeaf->isFull == true){			// third insertion, object number exceed leaf size by 1, need to use treeNode now
				rootNode = new treeNode();
				if(user.get_perm() < rootLeaf->getSmallerPerm()){		// third user's perm is the smallest
					rootNode->leafChildren[0] = new treeLeaf(user);
					rootNode->leafChildren[1] = rootLeaf;
					rootNode->perms[0] = leafChildren[1]->getSmallerPerm();
					rootNode->indexUsed++;
				}else if(user.get_perm() > rootLeaf->getLargerPerm()){				// third user's perm is the greatest
					rootNode->leafChildren[1] = new treeLeaf(user);
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->perms[0] = leafChildren[1]->getSmallerPerm();
					rootNode->indexUsed++;												// third user's perm is in between of the first and second
				}else{
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->leafChildren[1] = new treeLeaf(*(rootNode->leafChildren[0]->userTwo));	// rearrange, place the smaller two user on the first leaf, largest one user on the second leaf
					rootNode->leafChildren[0]->userTwo = new userInfo(user);
					rootNode->perms[0] = leafChildren[1]->getSmallerPerm();	
					rootNode->indexUsed++;
				}
				isOnlyLeaf = false;
				rootLeaf = NULL;
			}
		}
		else if( isOnlyLeaf == false){
			find_and_insert(user, rootNode);
		}
	}



	void break_up(treeNode* current){

		if(current->parent == NULL){
			if(current->isAboveLeaf == true){

				current = new treeNode();
				current->isAboveLeaf = false;

				current->nodeChildren[0] = new treeNode();
				current->nodeChildren[0]->parent = current;
				current->nodeChildren[0]->leafChildren[0] = new treeLeaf(rootNode->leafChildren[0]);
				current->nodeChildren[0]->leafChildren[1] = new treeLeaf(rootNode->leafChildren[1]);
				current->nodeChildren[0]->perms[0] = current->nodeChildren[0]->leafChildren[1]->getSmallerPerm();
				current->nodeChildren[0]->indexUsed++;

				current->nodeChildren[1] = new treeNode();
				current->nodeChildren[1]->parent = current;
				current->nodeChildren[1]->leafChildren[0] = new treeLeaf(rootNode->leafChildren[2]);
				current->nodeChildren[1]->leafChildren[1] = new treeLeaf(rootNode->leafChildren[3]);
				current->nodeChildren[1]->perm[0] = current->nodeChildren[1]->leafChildren[1]->getSmallerPerm();
				current->nodeChildren[1]->indexUsed++;

				current->perm[0] = current->nodeChildren[1]->leafChildren[0]->getSmallerPerm();
				current->indexUsed++;

				delete rootNode;
				rootNode = current;

			}else if(current->isAboveLeaf == false){

				current = new treeNode();
				current->isAboveLeaf = false;

				current->nodeChildren[0] = new treeNode();
				current->nodeChildren[0]->isAboveLeaf = false;
				current->nodeChildren[0]->parent = current;
				current->nodeChildren[0]->nodeChildren[0] = new treeNode(rootNode->nodeChildren[0]);
				current->nodeChildren[0]-nodeChildren[0]->parent = current->nodeChildren[0];
				current->nodeChildren[0]->leafChildren[1] = new treeNode(rootNode->nodeChildren[1]);
				current->nodeChildren[0]-nodeChildren[1]->parent = current->nodeChildren[0];
				current->nodeChildren[0]->perms[0] = get_node_index(current->nodeChildren[0]);				//error
				current->nodeChildren[0]->indexUsed++;

				current->nodeChildren[1] = new treeNode();
				current->nodeChildren[1]->isAboveLeaf = false;
				current->nodeChildren[1]->parent = current;
				current->nodeChildren[1]->nodeChildren[0] = new treeNode(rootNode->nodeChildren[2]);
				current->nodeChildren[1]-nodeChildren[0]->parent = current->nodeChildren[1];
				current->nodeChildren[1]->leafChildren[1] = new treeNode(rootNode->nodeChildren[3]);
				current->nodeChildren[1]-nodeChildren[1]->parent = current->nodeChildren[1];
				current->nodeChildren[1]->perms[0] = get_node_index(current->nodeChildren[1]);
				current->nodeChildren[1]->indexUsed++;

				current->perm[0] = get_node_index(current);
				current->indexUsed++;

				delete rootNode;
				rootNode = current;

			}

		}else{
			if(current->parent->isNodefull == false){
				if(current->parent->indexUsed == 1){
					if(current == current->parent->nodeChildren[0]){
						if(current->isAboveLeaf == true){

							current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

							current->parengt->nodeChildren[1] = new treeNode();
							current->parent->nodeChildren[1]->parent = current->parent;
							current->parent->nodeChildren[1]->leafChildren[0] = current->leafChildren[2];
							current->parent->nodeChildren[1]->leafChildren[1] = current->leafChildren[3];
							current->parent->nodeChildren[1]->perms[0] = current->parent->nodeChildren[1]->leafChildren[1].getSmallerPerm();
							current->parent->nodeChildren[1]->indexUsed++;

							current->leafChildren[2] = NULL;
							current->leafChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->indexUsed++;

						}else{

							current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

							current->parengt->nodeChildren[1] = new treeNode();
							current->parent->nodeChildren[1]->parent = current->parent;
							current->parent->nodeChildren[1]->isAboveLeaf = false;
							current->parent->nodeChildren[1]->nodeChildren[0] = current->nodeChildren[2];
							current->parent->nodeChildren[1]->nodeChildren[1] = current->nodeChildren[3];
							current->parent->nodeChildren[1]->perms[0] = get_node_index(current->parent->nodeChildren[1]->nodeChildren[1]);
							current->parent->nodeChildren[1]->indexUsed++;

							current->nodeChildren[2] = NULL;
							current->nodeChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->indexUsed++;

						}

					}else if(current == current->parent->nodeChildren[1]){
						if(current->isAboveLeaf == true){

							current->parengt->nodeChildren[2] = new treeNode();
							current->parent->nodeChildren[2]->parent = current->parent;
							current->parent->nodeChildren[2]->leafChildren[0] = current->leafChildren[2];
							current->parent->nodeChildren[2]->leafChildren[1] = current->leafChildren[3];
							current->parent->nodeChildren[2]->perms[0] = current->parent->nodeChildren[2]->leafChildren[1].getSmallerPerm();
							current->parent->nodeChildren[2]->indexUsed++;

							current->leafChildren[2] = NULL;
							current->leafChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->indexUsed++;

						}else{

							current->parengt->nodeChildren[2] = new treeNode();
							current->parent->nodeChildren[2]->parent = current->parent;
							current->parent->nodeChildren[2]->isAboveLeaf = false;
							current->parent->nodeChildren[2]->nodeChildren[0] = current->nodeChildren[2];
							current->parent->nodeChildren[2]->nodeChildren[1] = current->nodeChildren[3];
							current->parent->nodeChildren[2]->perms[0] = get_node_index(current->parent->nodeChildren[2]->nodeChildren[1]);
							current->parent->nodeChildren[2]->indexUsed++;

							current->nodeChildren[2] = NULL;
							current->nodeChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->indexUsed++;

						}
					}

				}else if(current->parent->indexUsed == 2){
					if(current == current->parent->nodeChildren[0]){
						if(current->isAboveLeaf == true){

							current->parent->nodeChildren[3] = current->parent->nodeChildren[2];
							current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

							current->parent->nodeChildren[1] = new treeNode();
							current->parent->nodeChildren[1]->parent = current->parent;
							current->parent->nodeChildren[1]->leafChildren[0] = current->leafChildren[2];
							current->parent->nodeChildren[1]->leafChildren[1] = current->leafChildren[3];
							current->parent->nodeChildren[1]->perms[0] = current->parent->nodeChildren[1]->leafChildren[1].getSmallerPerm();
							current->parent->nodeChildren[1]->indexUsed++;

							current->leafChildren[2] = NULL;
							current->leafChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;


						}else{

							current->parent->nodeChildren[3] = current->parent->nodeChildren[2];
							current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

							current->parent->nodeChildren[1] = new treeNode();
							current->parent->nodeChildren[1]->parent = current->parent;
							current->parent->nodeChildren[1]->nodeChildren[0] = current->nodeChildren[2];
							current->parent->nodeChildren[1]->nodeChildren[1] = current->nodeChildren[3];
							current->parent->nodeChildren[1]->perms[0] = get_node_index(current->parent->nodeChildren[1]->nodeChildren[1]);
							current->parent->nodeChildren[1]->indexUsed++;

							current->nodeChildren[2] = NULL;
							current->nodeChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;

						}

					}else if(current == current->parent->nodeChildren[1]){
						if(current->isAboveLeaf == true){

							current->parent->nodeChildren[3] = current->parent->nodeChildren[2];

							current->parent->nodeChildren[2] = new treeNode();
							current->parent->nodeChildren[2]->parent = current->parent;
							current->parent->nodeChildren[2]->leafChildren[0] = current->leafChildren[2];
							current->parent->nodeChildren[2]->leafChildren[1] = current->leafChildren[3];
							current->parent->nodeChildren[2]->perms[0] = current->parent->nodeChildren[2]->leafChildren[1].getSmallerPerm();
							current->parent->nodeChildren[2]->indexUsed++;

							current->leafChildren[2] = NULL;
							current->leafChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;

						}else{

							current->parent->nodeChildren[3] = current->parent->nodeChildren[2];

							current->parent->nodeChildren[2] = new treeNode();
							current->parent->nodeChildren[2]->parent = current->parent;
							current->parent->nodeChildren[2]->nodeChildren[0] = current->nodeChildren[2];
							current->parent->nodeChildren[2]->nodeChildren[1] = current->nodeChildren[3];
							current->parent->nodeChildren[2]->perms[0] = get_node_index(current->parent->nodeChildren[2]->nodeChildren[1]);
							current->parent->nodeChildren[2]->indexUsed++;

							current->nodeChildren[2] = NULL;
							current->nodeChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;

						}

					}else if(current == current->parent->nodeChildren[2]){
						if(current->isAboveLeaf == true){

							current->parent->nodeChildren[3] = new treeNode();
							current->parent->nodeChildren[3]->parent = current->parent;
							current->parent->nodeChildren[3]->leafChildren[0] = current->leafChildren[2];
							current->parent->nodeChildren[3]->leafChildren[1] = current->leafChildren[3];
							current->parent->nodeChildren[3]->perms[0] = current->parent->nodeChildren[3]->leafChildren[1].getSmallerPerm();
							current->parent->nodeChildren[3]->indexUsed++;

							current->leafChildren[2] = NULL;
							current->leafChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;

						}else{

							current->parent->nodeChildren[3] = new treeNode();
							current->parent->nodeChildren[3]->parent = current->parent;
							current->parent->nodeChildren[3]->nodeChildren[0] = current->nodeChildren[2];
							current->parent->nodeChildren[3]->nodeChildren[1] = current->nodeChildren[3];
							current->parent->nodeChildren[3]->perms[0] = get_node_index(current->parent->nodeChildren[3]->nodeChildren[1]);
							current->parent->nodeChildren[3]->indexUsed++;

							current->nodeChildren[2] = NULL;
							current->nodeChildren[3] = NULL;
							current->perm[1] = 0;
							current->perm[2] = 0;
							current->indexUsed = 1;
							current->isNodefull = false;

							current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
							current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
							current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
							current->parent->indexUsed++;
							current->parent->isNodefull = true;

						}

					}

				}

			}else{
				break_up(current->parent);

			}
		}

	}



	void B_Tree::find_and_insert(userInfo user, treeNode* root){				

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

						}else if(perm < root->leafChildren[0]->getLargerPerm() && perm > root->leafChildren[0]->getSmallerPerm()){				// the case that perm is in between of the largerer and smaller user perms

							root->leafChildren[2] = root->leafChildren[1];																		// push the exsiting larger user to a new leaf

							root->leafChildren[1] = new treeLeaf(*(root->leafChildren[0]->userTwo));

							root->leafChildren[0]->userTwo = new userInfo(user);

						}else if(perm < root->leafChildren[0]->getSmallerPerm()){																// the case that perm is smaller than the smaller user perm

							root->leafChildren[2] = root->leafChildren[1];																		// allocate a new leaf on the left for the perm

							root->leafChildren[1] = root->leafChildren[0];

							root->leafChildren[0] = new treeLeaf(user);

						}

						root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

						root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						indexUsed++;

					}

				}else if( perm > root->perms[0]){

					if(root->leafChildren[1]->isLeafFull == false){				// go to the correct leaf, if it is not full, just insert

						root->leafChildren[1]->insert(user);

					}else{														//if the correct leaf is full
						
						if(perm < root->leafChildren[1]->getLargerPerm()){					// the case that the perm we want to insert is in between of the larger and smaller user

							root->leafChildren[2] = new treeLeaf(*(root->leafChildren[1]->userTwo));			// push the existing larger user to new leaf

							root->leafChildren[1]-userTwo = new userInfo(user);

						}else if(perm > root->leafChildren[1]->getLargerPerm()){			// the case that the perm is greater than the larger user

							root->leafChildren[2] = new treeLeaf(user);									// allocate a new leaf for the new perm on the right(largest)

						}

						root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

						root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						indexUsed++;

					}

				}
				
			}else if(root->indexUsed == 2){					// if there are two indexs available

				if(perm < root->perms[0]){								// goes to the first leaf(left most)

					if(root->leafChildren[0]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[0]->insert(user);

					}else{															// if it is full

						if(perm > root->leafChildren[0]->getLargerPerm()){

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = new treeLeaf(user);

						}else if(perm < root->leafChildren[0]->getLargerPerm() && perm > root->leafChildren[0]->getSmallerPerm()){

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = new treeLeaf(*(root->leafChildren[0]->userTwo));

							root->leafChildren[0]->userTwo = new userInfo(user);

						}else{

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = root->leafChildren[0];

							root->leafChildren[0] = new treeLeaf(user);

						}

						root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

						root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						root->perm[2] = root->leafChildren[3]->getSmallerPerm();

						indexUsed++;

						isNodeFull = true;
					}
					
				else if(perm > perms[0] && perm < perms[1]){			// goes to the second leaf(in between)

					if(root->leafChildren[1]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[1]->insert(user);

					}else{															// if it is full

						if(perm < root->leafChildren[1]->getLargerPerm()){

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = new treeLeaf(*(root->leafChildren[1]->userTwo));

							root->leafChildren[1]->userTwo = new userInfo(user);

						}else if(perm > root->leafChildren[1]->getLargerPerm()){

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = new treeLeaf(user);

						}

						root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

						root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						root->perm[2] = root->leafChildren[3]->getSmallerPerm();

						indexUsed++;

						isNodeFull = true;

					}

				}else{													// goes to the third leaf(right most)

					if(root->leafChildren[2]->isLeafFull == false){				// go to the correct leaf, if it is not full, just insert

						root->leafChildren[2]->insert(user);

					}else{

						if(perm < root->leafChildren[2]->getLargerPerm()){

							root->leafChildren[3] = new treeLeaf(*(root->leafChildren[2]->userTwo));

							root->leafChildren[2]->userTwo = new userInfo(user);

						}else if(perm > root->leafChildren[2]->getLargerPerm()){

							root->leafChildren[3] = new treeLeaf(user);

						}

						root->perm[0] = root->leafChildren[1]->getSmallerPerm();															// adjust index

						root->perm[1] = root->leafChildren[2]->getSmallerPerm();

						root->perm[2] = root->leafChildren[3]->getSmallerPerm();

						indexUsed++;

						isNodeFull = true;

					}

			}else if(root->indexUsed == 3){

				if(perm < root->perms[0]){

					if(root->leafChildren[0]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[0]->insert(user);

					}else{

						break_up(root);

						find_and_insert(user, root);

					}
					
				}else if(perm >= perms[0] && perm < perms[1]){

					if(root->leafChildren[1]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[1]->insert(user);

					}else{

						break_up(root);

						find_and_insert(user, root);

					}
					
				}else if(perm >= perms[1] && perm < perms[2]){

					if(root->leafChildren[2]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[2]->insert(user);

					}else{

						break_up(root);

						find_and_insert(user, root);

					}
					
				}else{

					if(root->leafChildren[3]->isLeafFull == false){					// if it is not full, just insert

						root->leafChildren[3]->insert(user);

					}else{

						break_up(root);

						find_and_insert(user, root);

					}

				}

			}

		}else{

			if(perm < root->perms[0]){

				find_and_insert(user, root->nodeChildren[0]);

			}else if(perm > root->perms[indexUsed - 1]){

				find_and_insert(user, root->nodeChildren[indexUsed]);

			}else if(indexUsed == 2){

				if(perm >= root->perms[0] && perm < root->perms[1]){

					find_and_insert(user, root->nodeChildren[1]);
				}

			}else if(indexUsed == 3){

				if(perm >= root->perms[0] && perm < root->perms[1]){

					find_and_insert(user, root->nodeChildren[1]);

				}else if(perm >= perms[1] && perm < perms[2]){

					find_and_insert(user, root->nodeChildren[2]);

				}
			}															
		}
																				
	}






