#include "friendRecommender.h"

using namespace std;

friendRecommender:: friendRecommender() {
    tree = new B_Tree();
    graph = new Relation_Graph();
}

void friendRecommender:: add_a_user(userInfo user, vector<int> friends) {   //The function will be called with parameters of perm number, name, 2 favorite movie genres and a list of perm numbers representing the user’s friends. 参数可能要改
    graph->insert_relation(user.get_perm(), friends);   //可以先把参数传进来在这个函数里面创立一个userInfo object.
    int index = graph->get_index(user.get_perm());
    //userInfo user(int perm, string name, string genre1, string genre2);
    tree->add_user(user);   //tree insert needs the index
}

bool friendRecommender:: find_a_user(int perm) {

}

void friendRecommender:: find_a_user_details(int perm) {

}

void friendRecommender:: recommend_friends(int perm) {

}