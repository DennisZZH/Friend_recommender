#include "friendRecommender.h"
#include "B_Tree.h"
#include "Relation_Graph.h"
#include "userInfo.h"
#include <fstream>

using namespace std;

vector<int> ParseFriends(string friends);

int main() {
	cout << "Hello, welcome to the Friend Recommender System.\n";
	string WelcomeMessage;
	friendRecommender Recommender;
	WelcomeMessage += "Please make the one of the following choices.\n";
	WelcomeMessage += "a) Input file.\n";
	WelcomeMessage += "b) Add a user.\n";
	WelcomeMessage += "c) Find a user.\n";
	WelcomeMessage += "d) Find a user’s details.\n";
	WelcomeMessage += "e) Recommend friends.\n";
	WelcomeMessage += "f) Exit the program.\n";
	cout << WelcomeMessage;
	char Input;
	int perm;
	string name;
	string genre1;
	string genre2;
	string friends;
	vector<int> parsed_friends;
	cin >> Input;

	while (Input != 'f') {
		switch (Input) {
			case 'a':
				std::cout << "Input file.\n";
				cout << "Inputting the file...\n";
				Recommender.InputFile("/Users/alphajun/Downloads/users_friendship.txt");
				cout << "Done!\n";
				break;
			case 'b':
				std::cout << "Add a user.\n";
				cout << "Input perm:\n"; cin >> perm;
				cout << "Input name:\n"; cin >> name;
				cout << "Input genre1:\n"; cin >> genre1;
				cout << "Input genre2:\n"; cin >> genre2;
				cout << "Input friends:\n"; cin >> friends;
				parsed_friends = ParseFriends(friends);
				Recommender.add_a_user(perm, name, genre1, genre2, parsed_friends);
				break;
			case 'c':
				std::cout << "Find a user.\n";
				cout << "Input perm:\n"; cin >> perm;
				Recommender.find_a_user(perm);
				break;
			case 'd':
				std::cout << "Find a user’s details.\n";
				cout << "Input perm:\n"; cin >> perm;
				Recommender.find_a_user_details(perm);
				break;
			case 'e':
				std::cout << "Recommend friends.\n";
				cout << "Input perm:\n"; cin >> perm;
				Recommender.recommend_friends(perm);
				break;
			default:
				std::cout << "Wrong operation! Please choose again.\n";
				break;
		}
		cout << WelcomeMessage;
		cin >> Input;
		cout << "Your choice is: " << Input << endl;
	}
	cout << "Thank you for using the program!\n";
	return 0;
}

vector<int> ParseFriends(string friends) {
	unsigned long NextSemicolonIndex;
	vector<int> ParsedFriends;
	string ParseNext = friends;
	NextSemicolonIndex = ParseNext.find(';');
	while (NextSemicolonIndex != -1) {
		ParsedFriends.push_back(stoi(ParseNext.substr(0, NextSemicolonIndex)));
		ParseNext = string(ParseNext.begin() + NextSemicolonIndex + 1, ParseNext.end());
		NextSemicolonIndex = ParseNext.find(';');
	}
	ParsedFriends.push_back(stoi(ParseNext.substr(0, NextSemicolonIndex)));

	return ParsedFriends;
}