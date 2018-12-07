#include "friendRecommender.h"

using namespace std;

friendRecommender:: friendRecommender() {
    tree = new B_Tree();
    graph = new Relation_Graph();
}

void friendRecommender:: InputFile(const string &reference) {
	int perm;
	unsigned long NextSemicolonIndex;
	string name;
	string genre1;
	string genre2;
	string ParseNext;   //substring after the next semicolon of the input word line
	ifstream file;
	file.open(reference);
	if (!file.is_open()) {
		cerr << "Failed to open the file.\n";
		exit(0);
	}
	string Word;
	while (file >> Word) {
		name = "";
		vector<int> ParsedFriends;
		ParseNext = Word;

		cout << ParseNext;        // print out the current input line

		NextSemicolonIndex = ParseNext.find(';');
		perm = stoi(ParseNext.substr(0, NextSemicolonIndex));

		if (ParseNext.find_last_of(';') == NextSemicolonIndex) {
			name += ParseNext.substr(NextSemicolonIndex + 1, ParseNext.length() - NextSemicolonIndex) + " ";
			file >> ParseNext;
			cout << " " << ParseNext << "\n";
		}
		else {
			ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
			cout << "\n";
		}
		NextSemicolonIndex = ParseNext.find(';');
		name += ParseNext.substr(0, NextSemicolonIndex);

		ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
		NextSemicolonIndex = ParseNext.find(';');
		genre1 = ParseNext.substr(0, NextSemicolonIndex);

		ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
		NextSemicolonIndex = ParseNext.find(';');
		genre2 = ParseNext.substr(0, NextSemicolonIndex);

		ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
		NextSemicolonIndex = ParseNext.find(';');
		while (NextSemicolonIndex != -1) {
			ParsedFriends.push_back(stoi(ParseNext.substr(0, NextSemicolonIndex)));
			ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
			NextSemicolonIndex = ParseNext.find(';');
		}
		ParsedFriends.push_back(stoi(ParseNext.substr(0, NextSemicolonIndex)));

		add_a_user(perm, name, genre1, genre2, ParsedFriends);
	}
}

void friendRecommender:: add_a_user(int perm, string name, string genre1, string genre2, vector<int> friends) {
    graph->insert_relation(perm, friends);
    int index = graph->get_index(perm);
    userInfo user(perm, name, genre1, genre2, index);
    tree->add_user(user);
}

bool friendRecommender:: find_a_user(int perm) {
	if (!tree->find_user(perm)) {
         cout << "FAILED! User with perm " << perm << " NOT FOUND!" << endl;
         return false;
    } else {
        cout << "SUCCEED! User with perm " << perm << " FOUND!" << endl;
        return true;
    }
}

void friendRecommender:: find_a_user_details(int perm) {
    if (!find_a_user(perm)) {
        cout << "User with perm " << perm << " NOT FOUND!" << endl;
    } else {
        cout << tree->get_userInfo(perm).get_perm() << ";" << tree->get_userInfo(perm).get_name() << ";" << tree->get_userInfo(perm).get_genre1() << ";" << tree->get_userInfo(perm).get_genre2() << ";";

        vector<int> friends = graph->friendship_graph[tree->get_userInfo(perm).get_graph_index()];
        for (auto i = friends.begin() + 1; i !=friends.end(); i++) {
            cout << *i << ";";
        }
        cout << endl;
    }
}

 void friendRecommender:: recommend_friends(int perm) {
    int index = tree->get_userInfo(perm).get_graph_index();

    vector<int> CurrentFriends (graph->friendship_graph[index].begin(), graph->friendship_graph[index].end());

    queue<int> queue;
    queue.push(perm);
    vector<bool> visited;
    visited.resize(2 * graph->friendship_graph.size());
    for (int i = 0; i <= graph->friendship_graph.size(); i++) {
    	visited[i] = false;
    }
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
            string PermUserGenre1 = tree->get_userInfo(perm).get_genre1();
            string PermUserGenre2 = tree->get_userInfo(perm).get_genre2();
            string FrontUserGenre1 = tree->get_userInfo(front).get_genre1();
            string FrontUserGenre2 = tree->get_userInfo(front).get_genre2();

            if (PermUserGenre1 == FrontUserGenre1 or    //compare the genres of the two users
                PermUserGenre1 == FrontUserGenre2 or
                PermUserGenre2 == FrontUserGenre1 or
                PermUserGenre2 == FrontUserGenre2) {
                cout << "< " << tree->get_userInfo(front).get_perm() << ", "    //print the friend that matches
                    << tree->get_userInfo(front).get_name() << ", "
                    << FrontUserGenre1 << ", "
                    << FrontUserGenre2 << " >\n";
            }
        }

        int FrontIndex = tree->get_userInfo(front).get_graph_index();

        //enqueue all adjacent nodes of front and mark them visited
        for (int &i : graph->friendship_graph[FrontIndex]) {
            if (!visited[i]) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
}