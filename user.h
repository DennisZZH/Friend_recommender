//
// Created by Jiajun Wan on 2018-12-03.
//

#ifndef FRIEND_RECOMMENDER_USER_H
#define FRIEND_RECOMMENDER_USER_H

#include <string>

class user {
public:

	user() = default;
	user(int perm, std::string name, std::string genre1, std::string genre2);

	int get_perm(){ return perm;};			// getter functions
	std::string get_name(){ return name;};
	std::string get_genre1(){ return genre1;};
	std::string get_genre2(){ return genre2;};

private:
	int perm; // unique id
	std::string name ; // name of the person
	std::string genre1 ; // first favorite movie genre
	std::string genre2 ; // second favorite movie genre
};


#endif //FRIEND_RECOMMENDER_USER_H
