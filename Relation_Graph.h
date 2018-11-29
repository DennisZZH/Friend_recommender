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

class Relation_Graph{

public:

	vector<vector<int> > friendship_graph;    //public member, represented using adjacency list vector of vectors

	Relation_Graph() = default;		//constructor
	void insert_relation(int MyPerm, vector<int> friends);

};
#endif