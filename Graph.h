//Author: Zihao Zhang
//Date: 11.25
#ifndef GRAPH.H
#define GRAPH.H

#include <cstdlib>
#include <iostream>
#include <string>

#include "graphNode.h"

using namespace std;

class graphNode;

class Graph{

public:

	Graph();		// constructor

	insert_relation(list<int> friends);

private:

	list<graphNode*> friendship;
	
};
#endif