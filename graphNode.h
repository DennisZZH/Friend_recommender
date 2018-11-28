//Author: Zihao Zhang
//Date: 11.25
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class graphNode{

public:

	graphNode();		// default constructor

	graphNode(int perm);	// constructor

	int get_perm(){ return perm;};	// getter functions
	
private:
	int perm ; // unique id
	graphNode* next; // pointer to next node
};
#endif