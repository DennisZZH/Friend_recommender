//Author: Zihao Zhang
//Date: 11.25
#ifndef FRIENDRECOMMENDER_H
#define FRIENDRECOMMENDER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <queue>

#include "B_Tree.h"
#include "Relation_Graph.h"
#include "userInfo.h"

using namespace std;

class B_Tree;

class Graph;

class userInfo;

class friendRecommender{

public:

	friendRecommender();		// constructor

	void add_a_user(int perm, string name, string genre1, string genre2, vector<int> friends);

	bool find_a_user(int perm);

	void find_a_user_details(int perm);

	void recommend_friends(int perm);
	
private:
	
	B_Tree *tree;

	Relation_Graph *graph;

};
#endif