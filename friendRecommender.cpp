#include "friendRecommender.h"

using namespace std;

friendRecommender:: friendRecommender() {
    tree = new B_Tree();
    graph = new Relation_Graph();
}

void friendRecommender:: add_a_user(int perm, string name, string genre1, string genre2, vector<int> friends) {
    graph->insert_relation(perm, friends);
    int index = graph->get_index(perm);
    userInfo user(perm, name, genre1, genre2);
    tree->add_user(user);   //tree insertion needs the index; get add a new index parameter
}

bool friendRecommender:: find_a_user(int perm) {

}

void friendRecommender:: find_a_user_details(int perm) {

}

void friendRecommender:: recommend_friends(int perm) {
    int index = 0; //assign index = B_Tree.find_user_details.get_perm()

    vector<int> CurrentFriends (graph->friendship_graph[index].begin(), graph->friendship_graph[index].end());

    queue<int> queue;
    queue.push(perm);
    vector<bool> visited;
    visited[perm] = true;

    while (!queue.empty()) {
        int front = queue.front();
        queue.pop();

        bool isCurrentFriend = false;
        for (int element : CurrentFriends) {
            if (element == front) {
                isCurrentFriend = true;
                break;
            }
        }

        if (!isCurrentFriend) { //&& the genre is the same
            //clearly print the < perm number, name, 2 genres >
        }

        cout << front << " ";
        int FrontIndex = 0; //index = B_Tree.find_user_details.get_perm()

        // Enqueue all adjacent of front and mark them visited
        for (int &i : graph->friendship_graph[FrontIndex]) {
            if (!visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}