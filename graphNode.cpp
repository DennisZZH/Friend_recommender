//Author: Zihao Zhang
//Date: 11.25.2018
#include "graphNode.h"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

	graphNode::graphNode(int perm){
		this->perm = perm;
		this->next = NULL;
	}
