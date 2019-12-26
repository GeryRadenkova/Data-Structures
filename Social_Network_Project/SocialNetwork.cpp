#include "SocialNetwork.hpp"

SocialNetwork::SocialNetwork() : friend_list(8) {
	
}

bool SocialNetwork::create(std::string name, int age) {

	if (check_user(name)) //check if such user already exists
		return false;
		
	User* newUser = new User(name, age);
	users.push_back(newUser);

	hash_table.insert(std::pair<std::string, int>(name, users.size() - 1));

	return true;
}

bool SocialNetwork::link(std::string name1, std::string name2, friendship_type type) {
	
	std::map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::map<std::string, int>::iterator iter2 = hash_table.find(name2);

	if (friend_list.size() >= friend_list.max_size())
		friend_list.resize(friend_list.capacity() * 2);

	friend_list[iter1->second].push_back(std::pair<int, friendship_type>(iter2->second, type));
	friend_list[iter2->second].push_back(std::pair<int, friendship_type>(iter1->second, type));

	return true;
}

bool SocialNetwork::find(std::string name) {
	
	if (!check_user(name)) //check if user exists
		return false;

	std::map<std::string, int>::iterator iter = hash_table.find(name);
	users[iter->second]->print();
	print_friend_list(iter->second);

	return true;
}

bool SocialNetwork::ban(std::string name1, std::string name2) {
	
	if (!(check_user(name1) && check_user(name2))) //check that both users exist
		return false;

	std::map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::map<std::string, int>::iterator iter2 = hash_table.find(name2);

	ban_user(iter1->second, iter2->second, blocked);
	ban_user(iter2->second, iter1->second, being_blocked);

	return true;
}

bool SocialNetwork::remove(std::string name) {

	if (!check_user(name)) //check if user exists
		return false;

	std::map<std::string, int>::iterator iter = hash_table.find(name);

	for (int i = 0; i < friend_list[iter->second].capacity(); i++) 
		delink_user(friend_list[iter->second][i].first, iter->second);
	
	/*for (int i = 0; i < friend_list[iter->second].capacity(); i++) 
		delink_user(iter->second, friend_list[iter->second][i].first);*/

	friend_list.erase(friend_list.begin() + iter->second);
	hash_table.erase(iter);

	std::vector<User*>::iterator ptr = users.begin() + iter->second;//!!
	users.erase(ptr);
}

bool SocialNetwork::delink(std::string name1, std::string name2) {

	if (!(check_user(name1) && check_user(name2))) //check that both users exist
		return false;

	std::map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::map<std::string, int>::iterator iter2 = hash_table.find(name2);
	
	delink_user(iter1->second, iter2->second);
	delink_user(iter2->second, iter1->second);

	return true;
}

bool SocialNetwork::check_user(std::string name) {

	std::map<std::string, int>::iterator iter = hash_table.find(name);
	if (iter == hash_table.end())
		return false;
	return true;
}

void SocialNetwork::delink_user(int index, int user_pos) {

	for (int i = 0; i < friend_list[index].capacity(); i++) {
		if (friend_list[index][i].first == user_pos) {
			friend_list[index].erase(friend_list[index].begin() + i);
			return;
		}
	}
}

void SocialNetwork::ban_user(int index, int user_pos, friendship_type type) {

	for (int i = 0; i < friend_list[index].capacity(); i++) {
		if (friend_list[index][i].first == user_pos) {
			friend_list[index][i].second = type;
			return;
		}
	}
}

void SocialNetwork::print_friend_list(int index) {

	std::cout << "Friends: \n";

	for (int i = 0; i < friend_list[index].capacity(); i++)
		std::cout << users[friend_list[index][i].first]->name;
}