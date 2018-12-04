//Author: Zihao Zhang
//Date: 11.26
#include <cstdlib>
#include <iostream>
#include <string>

#include "treeLeaf.h"

using namespace std;

treeLeaf::treeLeaf(userInfo user){
	userOne = new userInfo(user);
}

void treeLeaf::insert(userInfo user){
	int perm = user.get_perm();
		
	if(perm > userOne->get_perm()){

		userTwo = new userInfo(user);

	}else{
			
		userTwo = userOne;

		userOne = new userInfo(user);
	}
}

int treeLeaf::getSmallerPerm(){

	return userOne->get_perm();
}

int treeLeaf::getLargerPerm(){

	return userTwo->get_perm();
	
}