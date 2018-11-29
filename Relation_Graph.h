//Author: Zihao Zhang
//Date: 11.25
#ifndef RELATION_GRAPH
#define RELATION_GRAPH

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "graphNode.h"

using namespace std;

class graphNode;

class Relation_Graph{

public:

	Relation_Graph();		// constructor

	void insert_relation(int MyPerm, vector<int> friends);

private:

	vector<vector<int> > friendship;
	
};
#endif