#include "SocialNetwork.hpp"

void SocialNetwork::print_friend_list(int index) {

	std::cout << "Friends: \n";

	for (int i = 0; i < friend_list[index].capacity(); i++) 
		std::cout << users[friend_list[index][i].first]->name;
}

SocialNetwork::SocialNetwork() : friend_list(8) {
	
}

bool SocialNetwork::create(std::string name, int age) {

	std::map<std::string, int>::iterator iter = hash_table.find(name);
	if (iter != hash_table.end() && iter->first == name)
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
	
	std::map<std::string, int>::iterator iter = hash_table.find(name);
	if (iter == hash_table.end())
		return false;

	users[iter->second]->print();
	print_friend_list(iter->second);

	return true;
}

void SocialNetwork::remove(std::string name) {

	
}

void SocialNetwork::delink(std::string name1, std::string name2) {

	std::map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::map<std::string, int>::iterator iter2 = hash_table.find(name2);
	
	for (int i = 0; i < friend_list[iter1->second].capacity(); i++) {
		//if (friend_list[iter1->first][i]->first == name1)
			friend_list[iter1->second].erase(friend_list[iter1->second].begin() + i);
	}

	for (int i = 0; i < friend_list[iter2->second].capacity(); i++) {
		if(iter2->first == name2)
			friend_list[iter2->second].erase(friend_list[iter2->second].begin() + i);
	}

}
