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

	void print() {
		std::cout << "User: ";
		std::cout << name << std::endl;
		std::cout << "Age: ";
		std::cout << age << std::endl;
	}
};

//struct Friend {
//	int user;
//	enum friendship_type { normal, relative, bestie };
//};

enum friendship_type { normal, relative, bestie };


class SocialNetwork {

private:
	std::vector<std::vector<std::pair<int, friendship_type>>> friend_list;
	std::map<std::string, int> hash_table;
	std::vector<User*> users;

	void print_friend_list(int index);

public:
	SocialNetwork();
	SocialNetwork(SocialNetwork& other) = delete;
	SocialNetwork& operator=(SocialNetwork& other) = delete;
	//~SocialNetwork();
	bool create(std::string name, int age);
	bool link(std::string name1, std::string name2, friendship_type type = normal);
	bool find(std::string name);

	void remove(std::string name);
	void delink(std::string name1, std::string name2);

};

#endif // !SOCIALNETWORK_HDR
