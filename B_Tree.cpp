//Author: Zihao Zhang
//Date: 11.26
#include <cstdlib>
#include <iostream>
#include <string>

#include "B_Tree.h"

using namespace std;

	B_Tree::B_Tree(){
		this->rootNode = NULL;
		this->rootLeaf = NULL;
		this->isOnlyLeaf = true;
	}

	void B_Tree::add_user(userInfo user) {
		if(isOnlyLeaf == true){							// in the case that there are only leaves.
			if(rootLeaf == NULL){							// 1st insertion, root points to a leaf
				rootLeaf = new treeLeaf(user);
			}else if(rootLeaf != NULL && rootLeaf->isLeafFull == false){						// second insertion, leaf full
				rootLeaf->insert(user);
				rootLeaf->isLeafFull = true;
			}else if(rootLeaf != NULL && rootLeaf->isLeafFull == true){			// third insertion, object number exceed leaf size by 1, need to use treeNode now
				rootNode = new treeNode();
				if(user.get_perm() < rootLeaf->getSmallerPerm()){		// third user's perm is the smallest
					rootNode->leafChildren[0] = new treeLeaf(user);
					rootNode->leafChildren[1] = rootLeaf;
					rootNode->perms[0] = rootNode->leafChildren[1]->getSmallerPerm();
					rootNode->indexUsed++;
				}else if(user.get_perm() > rootLeaf->getLargerPerm()){				// third user's perm is the greatest
					rootNode->leafChildren[1] = new treeLeaf(user);
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->perms[0] = rootNode->leafChildren[1]->getSmallerPerm();
					rootNode->indexUsed++;												// third user's perm is in between of the first and second
				}else{
					rootNode->leafChildren[0] = rootLeaf;
					rootNode->leafChildren[1] = new treeLeaf(*(rootNode->leafChildren[0]->userTwo));	// rearrange, place the smaller two user on the first leaf, largest one user on the second leaf
					rootNode->leafChildren[0]->userTwo = new userInfo(user);
					rootNode->perms[0] = rootNode->leafChildren[1]->getSmallerPerm();	
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

	void B_Tree::break_when_parent_not_full(treeNode* current){
	if(current->parent->indexUsed == 1){
		if(current == current->parent->nodeChildren[0]){
			if(current->isAboveLeaf == true){

				current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

				current->parent->nodeChildren[1] = new treeNode();
				current->parent->nodeChildren[1]->parent = current->parent;
				current->parent->nodeChildren[1]->leafChildren[0] = current->leafChildren[2];
				current->parent->nodeChildren[1]->leafChildren[1] = current->leafChildren[3];
				current->parent->nodeChildren[1]->perms[0] = current->parent->nodeChildren[1]->leafChildren[1]->getSmallerPerm();
				current->parent->nodeChildren[1]->indexUsed++;

				current->leafChildren[2] = NULL;
				current->leafChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->indexUsed++;

			}else{

				current->parent->nodeChildren[2] = current->parent->nodeChildren[1];

				current->parent->nodeChildren[1] = new treeNode();
				current->parent->nodeChildren[1]->parent = current->parent;
				current->parent->nodeChildren[1]->isAboveLeaf = false;
				current->parent->nodeChildren[1]->nodeChildren[0] = current->nodeChildren[2];
				current->parent->nodeChildren[1]->nodeChildren[1] = current->nodeChildren[3];
				current->parent->nodeChildren[1]->perms[0] = get_node_index(current->parent->nodeChildren[1]->nodeChildren[1]);
				current->parent->nodeChildren[1]->indexUsed++;

				current->nodeChildren[2] = NULL;
				current->nodeChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->indexUsed++;

			}

		}else if(current == current->parent->nodeChildren[1]){
			if(current->isAboveLeaf == true){

				current->parent->nodeChildren[2] = new treeNode();
				current->parent->nodeChildren[2]->parent = current->parent;
				current->parent->nodeChildren[2]->leafChildren[0] = current->leafChildren[2];
				current->parent->nodeChildren[2]->leafChildren[1] = current->leafChildren[3];
				current->parent->nodeChildren[2]->perms[0] = current->parent->nodeChildren[2]->leafChildren[1]->getSmallerPerm();
				current->parent->nodeChildren[2]->indexUsed++;

				current->leafChildren[2] = NULL;
				current->leafChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->indexUsed++;

			}else{

				current->parent->nodeChildren[2] = new treeNode();
				current->parent->nodeChildren[2]->parent = current->parent;
				current->parent->nodeChildren[2]->isAboveLeaf = false;
				current->parent->nodeChildren[2]->nodeChildren[0] = current->nodeChildren[2];
				current->parent->nodeChildren[2]->nodeChildren[1] = current->nodeChildren[3];
				current->parent->nodeChildren[2]->perms[0] = get_node_index(current->parent->nodeChildren[2]->nodeChildren[1]);
				current->parent->nodeChildren[2]->indexUsed++;

				current->nodeChildren[2] = NULL;
				current->nodeChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

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
				current->parent->nodeChildren[1]->perms[0] = current->parent->nodeChildren[1]->leafChildren[1]->getSmallerPerm();
				current->parent->nodeChildren[1]->indexUsed++;

				current->leafChildren[2] = NULL;
				current->leafChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;


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
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;

			}

		}else if(current == current->parent->nodeChildren[1]){
			if(current->isAboveLeaf == true){

				current->parent->nodeChildren[3] = current->parent->nodeChildren[2];

				current->parent->nodeChildren[2] = new treeNode();
				current->parent->nodeChildren[2]->parent = current->parent;
				current->parent->nodeChildren[2]->leafChildren[0] = current->leafChildren[2];
				current->parent->nodeChildren[2]->leafChildren[1] = current->leafChildren[3];
				current->parent->nodeChildren[2]->perms[0] = current->parent->nodeChildren[2]->leafChildren[1]->getSmallerPerm();
				current->parent->nodeChildren[2]->indexUsed++;

				current->leafChildren[2] = NULL;
				current->leafChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;

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
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;

			}

		}else if(current == current->parent->nodeChildren[2]){
			if(current->isAboveLeaf == true){

				current->parent->nodeChildren[3] = new treeNode();
				current->parent->nodeChildren[3]->parent = current->parent;
				current->parent->nodeChildren[3]->leafChildren[0] = current->leafChildren[2];
				current->parent->nodeChildren[3]->leafChildren[1] = current->leafChildren[3];
				current->parent->nodeChildren[3]->perms[0] = current->parent->nodeChildren[3]->leafChildren[1]->getSmallerPerm();
				current->parent->nodeChildren[3]->indexUsed++;

				current->leafChildren[2] = NULL;
				current->leafChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;

			}else{

				current->parent->nodeChildren[3] = new treeNode();
				current->parent->nodeChildren[3]->parent = current->parent;
				current->parent->nodeChildren[3]->nodeChildren[0] = current->nodeChildren[2];
				current->parent->nodeChildren[3]->nodeChildren[1] = current->nodeChildren[3];
				current->parent->nodeChildren[3]->perms[0] = get_node_index(current->parent->nodeChildren[3]->nodeChildren[1]);
				current->parent->nodeChildren[3]->indexUsed++;

				current->nodeChildren[2] = NULL;
				current->nodeChildren[3] = NULL;
				current->perms[1] = 0;
				current->perms[2] = 0;
				current->indexUsed = 1;
				current->isNodeFull = false;

				current->parent->perms[0] = get_node_index(current->parent->nodeChildren[1]);
				current->parent->perms[1] = get_node_index(current->parent->nodeChildren[2]);
				current->parent->perms[2] = get_node_index(current->parent->nodeChildren[3]);
				current->parent->indexUsed++;
				current->parent->isNodeFull = true;

			}
		}
	}
}

	void B_Tree:: break_up(treeNode* current){

		if(current->parent == NULL){
			if(current->isAboveLeaf == true){

				rootNode = new treeNode();
				rootNode->isAboveLeaf = false;

				rootNode->nodeChildren[1] = new treeNode();
				rootNode->nodeChildren[1]->parent = rootNode;
				rootNode->nodeChildren[1]->leafChildren[0] = current->leafChildren[2];
				rootNode->nodeChildren[1]->leafChildren[1] = current->leafChildren[3];
				rootNode->nodeChildren[1]->perms[0] = rootNode->nodeChildren[1]->leafChildren[1]->getSmallerPerm();
				rootNode->nodeChildren[1]->indexUsed++;

				rootNode->nodeChildren[0] = current;
				rootNode->nodeChildren[0]->parent = rootNode;
				rootNode->nodeChildren[0]->leafChildren[2] = NULL;
				rootNode->nodeChildren[0]->leafChildren[3] = NULL;
				rootNode->nodeChildren[0]->perms[1] = 0;
				rootNode->nodeChildren[0]->perms[2] = 0;
				rootNode->nodeChildren[0]->indexUsed = 1;
				rootNode->nodeChildren[0]->isNodeFull = false;

				rootNode->perms[0] = rootNode->nodeChildren[1]->leafChildren[0]->getSmallerPerm();
				rootNode->indexUsed++;

			}else if(current->isAboveLeaf == false){

				rootNode = new treeNode();
				rootNode->isAboveLeaf = false;

				rootNode->nodeChildren[1] = new treeNode();
				rootNode->nodeChildren[1]->isAboveLeaf = false;
				rootNode->nodeChildren[1]->parent = rootNode;
				rootNode->nodeChildren[1]->nodeChildren[0] = current->nodeChildren[2];
				rootNode->nodeChildren[1]->nodeChildren[0]->parent = rootNode->nodeChildren[1];
				rootNode->nodeChildren[1]->nodeChildren[1] = current->nodeChildren[3];
				rootNode->nodeChildren[1]->nodeChildren[1]->parent = rootNode->nodeChildren[1];
				rootNode->nodeChildren[1]->perms[0] = get_node_index(rootNode->nodeChildren[1]->nodeChildren[1]);				//error
				rootNode->nodeChildren[1]->indexUsed++;

				rootNode->nodeChildren[0] = current;
				rootNode->nodeChildren[0]->parent = rootNode;
				rootNode->nodeChildren[0]->nodeChildren[2] = NULL;
				rootNode->nodeChildren[0]->nodeChildren[3] = NULL;
				rootNode->nodeChildren[0]->perms[1] = 0;
				rootNode->nodeChildren[0]->perms[2] = 0;
				rootNode->nodeChildren[0]->indexUsed = 1;
				rootNode->nodeChildren[0]->isNodeFull = false;

				rootNode->perms[0] = get_node_index(rootNode->nodeChildren[1]);
				rootNode->indexUsed++;

			}

		}else{
			if(current->parent->isNodeFull == false){

				break_when_parent_not_full(current);
		
			}else{

				break_up(current->parent);
				break_when_parent_not_full(current);

			}
		}
	}



	void B_Tree:: find_and_insert(userInfo user, treeNode* root) {

		int perm = user.get_perm();

		if (root->isAboveLeaf == true) {                   // at the level of node that above leaves; base case

			if (root->indexUsed ==
			    1) {                        // if there is only one index available, which means this node has 2 children leaves

				if (perm <
				    root->perms[0]) {                        // if perm we want to insert is smaller than this index, we go to the right pointer (smaller side)

					if (root->leafChildren[0]->isLeafFull ==
					    false) {            // go to the correct leaf, if it is not full, just insert

						root->leafChildren[0]->insert(user);

						root->leafChildren[0]->isLeafFull = true;

					} else {                                                    // if the correct leaf is full
						if (perm >
						    root->leafChildren[0]->getLargerPerm()) {                // the case that perm we want to insert is greater than the larger perm of the leaf

							root->leafChildren[2] = root->leafChildren[1];                // allocate a new leaf for the perm

							root->leafChildren[1] = new treeLeaf(user);

						} else if (perm < root->leafChildren[0]->getLargerPerm() && perm >
						                                                            root->leafChildren[0]->getSmallerPerm()) {                // the case that perm is in between of the largerer and smaller user perms

							root->leafChildren[2] = root->leafChildren[1];                                                                        // push the exsiting larger user to a new leaf

							root->leafChildren[1] = new treeLeaf(*(root->leafChildren[0]->userTwo));

							root->leafChildren[0]->userTwo = new userInfo(user);

						} else if (perm <
						           root->leafChildren[0]->getSmallerPerm()) {                                                                // the case that perm is smaller than the smaller user perm

							root->leafChildren[2] = root->leafChildren[1];                                                                        // allocate a new leaf on the left for the perm

							root->leafChildren[1] = root->leafChildren[0];

							root->leafChildren[0] = new treeLeaf(user);

						}

						root->perms[0] = root->leafChildren[1]->getSmallerPerm();                                                            // adjust index

						root->perms[1] = root->leafChildren[2]->getSmallerPerm();

						root->indexUsed++;

					}

				} else if (perm > root->perms[0]) {

					if (root->leafChildren[1]->isLeafFull ==
					    false) {                // go to the correct leaf, if it is not full, just insert

						root->leafChildren[1]->insert(user);

						root->leafChildren[1]->isLeafFull = true;

					} else {                                                        //if the correct leaf is full

						if (perm <
						    root->leafChildren[1]->getLargerPerm()) {                    // the case that the perm we want to insert is in between of the larger and smaller user

							root->leafChildren[2] = new treeLeaf(
									*(root->leafChildren[1]->userTwo));            // push the existing larger user to new leaf

							root->leafChildren[1] -> userTwo = new userInfo(user);

						} else if (perm >
						           root->leafChildren[1]->getLargerPerm()) {            // the case that the perm is greater than the larger user

							root->leafChildren[2] = new treeLeaf(
									user);                                    // allocate a new leaf for the new perm on the right(largest)

						}

						root->perms[0] = root->leafChildren[1]->getSmallerPerm();                                                            // adjust index

						root->perms[1] = root->leafChildren[2]->getSmallerPerm();

						root->indexUsed++;

					}

				}

			} else if (root->indexUsed == 2) {                    // if there are two indexs available

				if (perm < root->perms[0]) {                                // goes to the first leaf(left most)

					if (root->leafChildren[0]->isLeafFull ==
					    false) {                    // if it is not full, just insert

						root->leafChildren[0]->insert(user);

						root->leafChildren[0]->isLeafFull = true;

					} else {                                                            // if it is full

						if (perm > root->leafChildren[0]->getLargerPerm()) {

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = new treeLeaf(user);

						} else if (perm < root->leafChildren[0]->getLargerPerm() &&
						           perm > root->leafChildren[0]->getSmallerPerm()) {

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = new treeLeaf(*(root->leafChildren[0]->userTwo));

							root->leafChildren[0]->userTwo = new userInfo(user);

						} else {

							root->leafChildren[3] = root->leafChildren[2];

							root->leafChildren[2] = root->leafChildren[1];

							root->leafChildren[1] = root->leafChildren[0];

							root->leafChildren[0] = new treeLeaf(user);

						}

						root->perms[0] = root->leafChildren[1]->getSmallerPerm();                                                            // adjust index

						root->perms[1] = root->leafChildren[2]->getSmallerPerm();

						root->perms[2] = root->leafChildren[3]->getSmallerPerm();

						root->indexUsed++;

						root->isNodeFull = true;

					}

				} else if ((perm > root->perms[0]) and (perm < root->perms[1])) {            // goes to the second leaf(in between)

						if (root->leafChildren[1]->isLeafFull ==
						    false) {                    // if it is not full, just insert

							root->leafChildren[1]->insert(user);

							root->leafChildren[1]->isLeafFull = true;

						} else {                                                            // if it is full

							if (perm < root->leafChildren[1]->getLargerPerm()) {

								root->leafChildren[3] = root->leafChildren[2];

								root->leafChildren[2] = new treeLeaf(*(root->leafChildren[1]->userTwo));

								root->leafChildren[1]->userTwo = new userInfo(user);

							} else if (perm > root->leafChildren[1]->getLargerPerm()) {

								root->leafChildren[3] = root->leafChildren[2];

								root->leafChildren[2] = new treeLeaf(user);

							}

							root->perms[0] = root->leafChildren[1]->getSmallerPerm();                                                            // adjust index

							root->perms[1] = root->leafChildren[2]->getSmallerPerm();

							root->perms[2] = root->leafChildren[3]->getSmallerPerm();

							root->indexUsed++;

							root->isNodeFull = true;

						}

					} else {                                                    // goes to the third leaf(right most)

						if (root->leafChildren[2]->isLeafFull ==
						    false) {                // go to the correct leaf, if it is not full, just insert

							root->leafChildren[2]->insert(user);

							root->leafChildren[2]->isLeafFull = true;

						} else {

							if (perm < root->leafChildren[2]->getLargerPerm()) {

								root->leafChildren[3] = new treeLeaf(*(root->leafChildren[2]->userTwo));

								root->leafChildren[2]->userTwo = new userInfo(user);

							} else if (perm > root->leafChildren[2]->getLargerPerm()) {

								root->leafChildren[3] = new treeLeaf(user);

							}

							root->perms[0] = root->leafChildren[1]->getSmallerPerm();                                                            // adjust index

							root->perms[1] = root->leafChildren[2]->getSmallerPerm();

							root->perms[2] = root->leafChildren[3]->getSmallerPerm();

							root->indexUsed++;

							root->isNodeFull = true;

						}

					}

			}else if (root->indexUsed == 3) {

						if (perm < root->perms[0]) {

							if (root->leafChildren[0]->isLeafFull ==
							    false) {                    // if it is not full, just insert

								root->leafChildren[0]->insert(user);

								root->leafChildren[0]->isLeafFull = true;

							} else {

								break_up(root);

								find_and_insert(user, root);

							}

						} else if (perm >= root->perms[0] && perm < root->perms[1]) {

							if (root->leafChildren[1]->isLeafFull ==
							    false) {                    // if it is not full, just insert

								root->leafChildren[1]->insert(user);

								root->leafChildren[1]->isLeafFull = true;

							} else {

								break_up(root);

								find_and_insert(user, root);

							}

						} else if (perm >= root->perms[1] && perm < root->perms[2]) {

							if (root->leafChildren[2]->isLeafFull ==
							    false) {                    // if it is not full, just insert

								root->leafChildren[2]->insert(user);

								root->leafChildren[2]->isLeafFull = true;

							} else {

								break_up(root);

								find_and_insert(user, root);

							}

						} else {

							if (root->leafChildren[3]->isLeafFull ==
							    false) {                    // if it is not full, just insert

								root->leafChildren[3]->insert(user);

								root->leafChildren[3]->isLeafFull = true;

							} else {

								break_up(root);

								find_and_insert(user, root);

							}
						}
					}

			} else {

					if (perm < root->perms[0]) {

						find_and_insert(user, root->nodeChildren[0]);

					} else if (perm > root->perms[root->indexUsed - 1]) {

						find_and_insert(user, root->nodeChildren[root->indexUsed]);

					} else if (root->indexUsed == 2) {

						if (perm >= root->perms[0] && perm < root->perms[1]) {

							find_and_insert(user, root->nodeChildren[1]);
						}

					} else if (root->indexUsed == 3) {

						if (perm >= root->perms[0] && perm < root->perms[1]) {

							find_and_insert(user, root->nodeChildren[1]);

						} else if (perm >= root->perms[1] && perm < root->perms[2]) {

							find_and_insert(user, root->nodeChildren[2]);

						}
					}
				}
			}
		
	

	userInfo B_Tree:: get_userInfo(int perm) {
		userInfo user;
		return user;    //stub
	}

	int B_Tree::get_node_index(treeNode* current){
		if(current->isAboveLeaf == true){
			return current->leafChildren[0]->getSmallerPerm();
		}else{
			return get_node_index(current->nodeChildren[0]);
		}

	}


















