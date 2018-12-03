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
    tree->add_user(user, index);
}

bool friendRecommender:: find_a_user(int perm) {

}

void friendRecommender:: find_a_user_details(int perm) {

}

void friendRecommender:: recommend_friends(int perm) {
    int index = tree->get_graph_index(perm);

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

        if (!isCurrentFriend) {
            userInfo PermUser = tree->get_userInfo(perm);
            userInfo FrontUser = tree->get_userInfo(front);
            string PermUserGenre1 = PermUser.get_genre1();
            string PermUserGenre2 = PermUser.get_genre2();
            string FrontUserGenre1 = FrontUser.get_genre1();
            string FrontUserGenre2 = FrontUser.get_genre2();

            if (PermUserGenre1 == FrontUserGenre1 or    //compare the genres of the two users
                PermUserGenre1 == FrontUserGenre2 or
                PermUserGenre2 == FrontUserGenre1 or
                PermUserGenre2 == FrontUserGenre2) {
                cout << "< " << FrontUser.get_perm() << ", "    //print the friend that matches
                    << FrontUser.get_name() << ", "
                    << FrontUserGenre1 << ", "
                    << FrontUserGenre2 << " >\n";
            }
        }

        int FrontIndex = tree->get_graph_index(front);

        //enqueue all adjacent nodes of front and mark them visited
        for (int &i : graph->friendship_graph[FrontIndex]) {
            if (!visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}