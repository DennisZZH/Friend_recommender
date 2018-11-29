#include "friendRecommender.h"

using namespace std;

friendRecommender:: friendRecommender() {
    tree = new B_Tree();
    graph = new Relation_Graph();
}

void friendRecommender:: add_a_user(userInfo user, vector<int> friends) {
    tree->add_user(user);
    graph->insert_relation(user.get_perm(), friends);
}

bool friendRecommender:: find_a_user(int perm) {

}

void friendRecommender:: find_a_user_details(int perm) {

}

void friendRecommender:: recommend_friends(int perm) {

}