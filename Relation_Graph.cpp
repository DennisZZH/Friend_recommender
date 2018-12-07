//
// Created by Jiajun Wan on 2018-11-28.
//
#include "Relation_Graph.h"

void Relation_Graph:: insert_relation(int MyPerm, vector<int> friends) {
	vector<int> entry;  //create a entry vector to be inserted
	entry.push_back(MyPerm);    //pushback the first MyPerm element in the first place
	entry.insert(entry.end(), friends.begin(), friends.end());  //concatenate the friends vector with the entry vector
	friendship_graph.push_back(entry);  //pushback the entry vector in the adjacency list vector
	bool contains = false;

	for (int FriendPerm : friends) {    //loop through the friends to find if a previous entry needs to be updated
		for (vector<int> &ListEntry : friendship_graph) {
			if (ListEntry[0] == FriendPerm) {
				for (int element : ListEntry) {
					if (element == MyPerm) {contains = true;}
				}
				if (!contains) {ListEntry.push_back(MyPerm);}
			}
		}
	}
}

int Relation_Graph:: get_index(int Perm) {
	int index = 0;
	for (vector<int> ListEntry : friendship_graph) {
		if (ListEntry[0] == Perm) {
			return index;
		}
		index ++;
	}
	return -1;  //not found
}

/* void Relation_Graph:: print_graph_test() {
	for (vector<int> entry : friendship_graph) {
		for (int element : entry) {
			cout << element << "->";
		}
		cout << "\n";
	}
}
*/