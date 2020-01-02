#ifndef SOCIALNETWORK_HDR
#define SOCIALNETWORK_HDR

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <tuple>

const int NAME_SIZE = 24;
const int MAX_RECOMMEND = 30;

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

enum friendship_type { normal, relative, bestie, blocked, being_blocked };


class SocialNetwork {

public:
	SocialNetwork();
	SocialNetwork(SocialNetwork& other) = delete;
	SocialNetwork& operator=(SocialNetwork& other) = delete;
	~SocialNetwork();
	bool create(std::string name, int age);
	int link(std::string name1, std::string name2, friendship_type type = normal);
	bool find(std::string name);
	bool ban(std::string name1, std::string name2);
	bool remove(std::string name);
	bool delink(std::string name1, std::string name2);
	void recommend(std::string name);

private:
	std::vector<std::vector<std::pair<int, friendship_type>>> friend_list;
	std::unordered_map<std::string, int> hash_table;
	std::vector<User*> users;
	std::queue<int> free_positions;

	bool contains_user(std::string name);
	bool contains_link(int index1, int index2);
	bool is_link_blocked(int index1, int index2);
	void delink_user(int index, int user_pos);
	void ban_user(int index, int user_pos, friendship_type type);
	void print_friend_list(int index);
	std::string convert_to_string(char* str, int size);
	std::tuple<std::vector<int>, int, int> get_all_distance2(int start);
	std::vector<int> count_mutual_friends(std::vector<int> distance2, int user);
	int count_mutual_friends(int user1, int user2);
	void selection_sort(std::vector<int>& arr1, std::vector<int>& arr2);
	void swap(std::vector<int>& arr, int i, int j);
	std::vector<int> most_popular(int user);

public:
	void store_in_file();
	void load_from_file();

};

#endif // !SOCIALNETWORK_HDR
