#include "SocialNetwork.hpp"

SocialNetwork::SocialNetwork() {
	
}

bool SocialNetwork::create(std::string name, int age) {

	//std::map<std::string, int>::iterator iter = hash_table.find(name);
	//if (hash_table.size() != 0 && iter->first == name)
	//	return false;
	
	User* newUser = new User(name, age);
	users.push_back(newUser);

	hash_table.insert(std::pair<std::string, int>(name, users.size() - 1));

	return true;
}

bool SocialNetwork::link(std::string name1, std::string name2, friendship_type type) {
	
	std::map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::map<std::string, int>::iterator iter2 = hash_table.find(name2);

	friend_list[iter1->second].push_back(std::pair<int, friendship_type>(iter2->second, type));
	friend_list[iter2->second].push_back(std::pair<int, friendship_type>(iter1->second, type));

	return true;
}
