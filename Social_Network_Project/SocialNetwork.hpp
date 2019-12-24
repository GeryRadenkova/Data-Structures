#ifndef SOCIALNETWORK_HDR
#define SOCIALNETWORK_HDR

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct User {
	std::string name;
	int age;

	User(std::string name, int age) {
		this->name = name;
		this->age = age;
	}
};

struct Friend {
	int user;
	enum friendship_type { normal, relative, bestie };
};

enum friendship_type { normal, relative, bestie };
//struct Pair {
//	User user;
//	std::vector<Friend> friend_list;
//};

class SocialNetwork {

private:
	std::vector<std::vector<std::pair<int, friendship_type>>> friend_list;
	std::map<std::string, int> hash_table;
	std::vector<User*> users;

	//unsigned hash_function(std::string key);
	//User* check_key_uniqueness(std::string key, int index);

public:
	SocialNetwork();
	SocialNetwork(SocialNetwork& other) = delete;
	SocialNetwork& operator=(SocialNetwork& other) = delete;
	//~SocialNetwork();
	bool create(std::string name, int age);
	bool link(std::string name1, std::string name2, friendship_type type = normal);

};

#endif // !SOCIALNETWORK_HDR
