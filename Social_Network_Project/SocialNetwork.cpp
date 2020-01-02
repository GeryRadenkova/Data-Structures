#include "SocialNetwork.hpp"

SocialNetwork::SocialNetwork() {

}

SocialNetwork::~SocialNetwork() {

}

bool SocialNetwork::create(std::string name, int age) {

	if (contains_user(name)) //check if such user already exists
		return false;

	User* newUser = new User(name, age);

	std::vector<std::pair<int, friendship_type>> new_vector;

	if (!free_positions.empty()) {

		users[free_positions.front()] = newUser;

		hash_table.insert(std::pair<std::string, int>(name, free_positions.front()));

		friend_list[free_positions.front()] = new_vector;

		free_positions.pop();
	}
	else {
		users.push_back(newUser);
		hash_table.insert(std::pair<std::string, int>(name, users.size() - 1));

		friend_list.push_back(new_vector);
	}

	return true;
}

int SocialNetwork::link(std::string name1, std::string name2, friendship_type type) {

	if (!(contains_user(name1) && contains_user(name2))) //check that both users exist
		return 1;

	std::unordered_map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::unordered_map<std::string, int>::iterator iter2 = hash_table.find(name2);

	if (contains_link(iter1->second, iter2->second) && contains_link(iter2->second, iter1->second) && is_link_blocked(iter1->second, iter2->second))
		return 2;

	if (contains_link(iter1->second, iter2->second) && contains_link(iter2->second, iter1->second)) //check if we already have this link
		return 3;

	friend_list[iter1->second].push_back(std::pair<int, friendship_type>(iter2->second, type));
	friend_list[iter2->second].push_back(std::pair<int, friendship_type>(iter1->second, type));

	return 3;
}

bool SocialNetwork::find(std::string name) {

	if (!contains_user(name)) //check if user exists
		return false;

	std::unordered_map<std::string, int>::iterator iter = hash_table.find(name);
	users[iter->second]->print();
	print_friend_list(iter->second);

	return true;
}

bool SocialNetwork::ban(std::string name1, std::string name2) {

	if (!(contains_user(name1) && contains_user(name2))) //check that both users exist
		return false;

	std::unordered_map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::unordered_map<std::string, int>::iterator iter2 = hash_table.find(name2);

	ban_user(iter1->second, iter2->second, blocked);
	ban_user(iter2->second, iter1->second, being_blocked);

	return true;
}

bool SocialNetwork::remove(std::string name) {

	if (!contains_user(name)) //check if user exists
		return false;

	std::unordered_map<std::string, int>::iterator iter = hash_table.find(name);

	for (int i = 0; i < friend_list[iter->second].size(); i++)
		delink_user(friend_list[iter->second][i].first, iter->second);

	free_positions.push(iter->second);

	hash_table.erase(iter);

	return true;
}

bool SocialNetwork::delink(std::string name1, std::string name2) {

	if (!(contains_user(name1) && contains_user(name2))) //check that both users exist
		return false;

	std::unordered_map<std::string, int>::iterator iter1 = hash_table.find(name1);
	std::unordered_map<std::string, int>::iterator iter2 = hash_table.find(name2);

	if (!(contains_link(iter1->second, iter2->second) && contains_link(iter2->second, iter1->second))) //check if we have this link
		return true;

	delink_user(iter1->second, iter2->second);
	delink_user(iter2->second, iter1->second);

	return true;
}

void SocialNetwork::recommend(std::string name) {

	std::unordered_map<std::string, int>::iterator iter = hash_table.find(name);

	if (friend_list[iter->second].size() == 0) {
		std::vector<int> users_to_recommend = most_popular(iter->second);
		for (int i = 0; i < users_to_recommend.size(); i++)
			std::cout << users[users_to_recommend[i]]->name << std::endl;

		return;
	}

	std::tuple<std::vector<int>, int, int> res = get_all_distance2(iter->second);
	int bestie_end = std::get<1>(res);
	int relative_end = std::get<2>(res);
	std::vector<int> distance2 = std::get<0>(res);

	std::vector<int> mutual_friends = count_mutual_friends(distance2, iter->second); 

	for (int i = 0; i < bestie_end; i++)
		mutual_friends[i] *= 3;
	for (int i = bestie_end + 1; i < relative_end; i++)
		mutual_friends[i] *= 2;

	selection_sort(distance2, mutual_friends);

	for (int i = 0; i < distance2.size(); i++)
		std::cout << users[distance2[i]]->name << std::endl;
}

bool SocialNetwork::contains_user(std::string name) {

	std::unordered_map<std::string, int>::iterator iter = hash_table.find(name);
	if (iter == hash_table.end())
		return false;
	return true;
}

bool SocialNetwork::contains_link(int index1, int index2) {

	for (int i = 0; i < friend_list[index1].size(); i++) {
		if (friend_list[index1][i].first == index2)
			return true;
	}
	return false;
}

bool SocialNetwork::is_link_blocked(int index1, int index2) {
	
	for (int i = 0; i < friend_list[index1].size(); i++) {
		if (friend_list[index1][i].first == index2 && friend_list[index1][i].second == being_blocked)
			return true;
	}
	return false;
}

void SocialNetwork::delink_user(int index, int user_pos) {

	for (int i = 0; i < friend_list[index].size(); i++) {
		if (friend_list[index][i].first == user_pos) {
			friend_list[index].erase(friend_list[index].begin() + i);
			return;
		}
	}
}

void SocialNetwork::ban_user(int index, int user_pos, friendship_type type) {

	for (int i = 0; i < friend_list[index].size(); i++) {
		if (friend_list[index][i].first == user_pos) {
			friend_list[index][i].second = type;
			return;
		}
	}
}

void SocialNetwork::print_friend_list(int index) {

	std::cout << "Friends: \n";

	if (friend_list[index].size() == 0) {
		std::cout << "none\n";
		return;
	}

	for (int i = 0; i < friend_list[index].size(); i++) {
		if (friend_list[index][i].second == blocked || friend_list[index][i].second == being_blocked)
			continue;

		std::cout << users[friend_list[index][i].first]->name << std::endl;
	}

	std::cout << std::endl;
}

std::string SocialNetwork::convert_to_string(char* str, int size) {

	std::string s = "";
	for (int i = 0; i < size; i++)
		s = s + str[i];
	return s;
}

std::tuple<std::vector<int>, int, int> SocialNetwork::get_all_distance2(int start) {

	int count_recommendations = 0;

	std::vector<int> dist1_normal;
	std::vector<int> dist1_relative;
	std::vector<int> dist1_bestie;
	bool* visited = new bool[friend_list.size()];
	for (int i = 0; i < friend_list.size(); i++)
		visited[i] = false;

	visited[start] = true;
	for (int i = 0; i < friend_list[start].size(); i++) {

		if (count_recommendations == MAX_RECOMMEND)
			break;

		if (friend_list[start][i].second == normal)
			dist1_normal.push_back(friend_list[start][i].first);
		else if (friend_list[start][i].second == relative)
			dist1_relative.push_back(friend_list[start][i].first);
		else if (friend_list[start][i].second == bestie)
			dist1_bestie.push_back(friend_list[start][i].first);
		visited[friend_list[start][i].first] = true;
	}
	std::vector<int> result;

	for (int i = 0; i < dist1_bestie.size(); i++) {

		for (int j = 0; j < friend_list[dist1_bestie[i]].size(); j++) {

			int current = friend_list[dist1_bestie[i]][j].first;
			if (!visited[current])
				result.push_back(current);
			visited[current] = true;
		}
	}
	int bestieMutualCount = result.size();

	for (int i = 0; i < dist1_relative.size(); i++) {

		for (int j = 0; j < friend_list[dist1_relative[i]].size(); j++) {

			int current = friend_list[dist1_relative[i]][j].first;
			if (!visited[current])
				result.push_back(current);
			visited[current] = true;
		}
	}
	int relativeMutualCount = result.size() - bestieMutualCount;
	for (int i = 0; i < dist1_normal.size(); i++) {

		for (int j = 0; j < friend_list[dist1_normal[i]].size(); j++) {

			int current = friend_list[dist1_normal[i]][j].first;
			if (!visited[current])
				result.push_back(current);
			visited[current] = true;
		}
	}

	delete[] visited;
	return std::make_tuple(result, bestieMutualCount, relativeMutualCount);
}

std::vector<int> SocialNetwork::count_mutual_friends(std::vector<int> distance2, int user) {

	std::vector<int> result;
	int count = 0;
	for (int i = 0; i < distance2.size(); i++) {
		count = count_mutual_friends(user, distance2[i]);
		result.push_back(count);
	}
	return result;
}

int SocialNetwork::count_mutual_friends(int user1, int user2) {

	int count = 0;
	for (int i = 0; i < friend_list[user1].size(); i++) {
		for (int j = 0; j < friend_list[user2].size(); j++) {
			if (friend_list[user1][i].first == friend_list[user2][j].first)
				count++;
		}
	}
	return count;
}

void SocialNetwork::selection_sort(std::vector<int>& users, std::vector<int>& mutual_friends_count) {

	for (int i = 0; i < mutual_friends_count.size() - 1; i++) {
		int max_index = i;
		for (int j = i + 1; j < mutual_friends_count.size(); j++) {
			if (mutual_friends_count[j] > mutual_friends_count[max_index])
				max_index = j;
		}
		swap(mutual_friends_count, i, max_index);
		swap(users, i, max_index);
	}
}

void SocialNetwork::swap(std::vector<int>& arr, int i, int j) {

	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

std::vector<int> SocialNetwork::most_popular(int user) {

	int count_recommendations = 0;
	std::queue<int> free_positions_temp = free_positions;
	bool isIn = false;

	std::vector<int> count_friends;
	std::vector<int> users;
	int count = 0;
	for (int i = 0; i < friend_list.size(); i++) {

		if (count_recommendations == MAX_RECOMMEND)
			break;

		if (i == user)
			continue;

		while(!free_positions_temp.empty()) {
			if (i == free_positions_temp.front()) {
				isIn = true;
				break;
			}
			free_positions_temp.pop();
		}

		free_positions_temp = free_positions;
		if (isIn) {
			isIn = false;
			continue;
		}

		for (int j = 0; j < friend_list[i].size(); j++) {
			if (!(friend_list[i][j].second == blocked || friend_list[i][j].second == being_blocked))
				count++;
		}
		count_friends.push_back(count);
		users.push_back(i);
		count = 0;
		count_recommendations++;
	}

	selection_sort(users, count_friends);
	return users;
}

void SocialNetwork::store_in_file() {

	std::ofstream file;
	file.open("socialNetwork.txt");

	if (!file) {
		std::cerr << "Fail to open file.\n";
		return;
	}

	file << "hash_table:\n";
	std::unordered_map<std::string, int>::iterator iter;
	for (int i = 0; i < hash_table.size(); i++) {
		if (!contains_user(users[i]->name))
			continue;
		iter = hash_table.find(users[i]->name);
		file << iter->first << ' ' << iter->second << '\n';
	}
	file << "end \n";

	file << "users:\n";
	for (int i = 0; i < users.size(); i++)
		file << users[i]->name << ' ' << users[i]->age << '\n';
	file << "end \n";

	file << "friend_list:\n";
	for (int i = 0; i < friend_list.size(); i++) {
		file << "index " << i << ':';
		int j = 0;
		for (j = 0; j < friend_list[i].size() - 1; j++)
			file << friend_list[i][j].first << ' ' << friend_list[i][j].second << ';';
		file << friend_list[i][j].first << ' ' << friend_list[i][j].second << '.';
		file << '\n';
	}
	file << "end \n";

	file << "free_positions:\n";
	std::queue<int> temp = free_positions;
	while (!temp.empty()) {
		file << temp.front();
		temp.pop();

		if (!temp.empty())
			file << ',';
		else
			file << '.';
	}

	file.close();
}

void SocialNetwork::load_from_file() {

	std::ifstream file;
	file.open("socialNetwork.txt");

	if (!file) {
		std::cerr << "Fail to open file.\n";
		return;
	}

	char header[NAME_SIZE];
	char str[NAME_SIZE];
	std::string name;

	file.getline(header, NAME_SIZE, '\n');
	while (true) {
		file.getline(str, NAME_SIZE, ' ');
		name = convert_to_string(str, strlen(str));

		if (!strcmp(str, "end"))
			break;

		int pos;
		file >> pos;
		file.get(); //get '\n'

		hash_table.insert(std::pair<std::string, int>(name, pos));
	}

	file.get(); //get '\n'
	file.getline(header, NAME_SIZE, '\n');
	int age;
	User* newUser;
	std::vector<std::pair<int, friendship_type>> new_vector;
	while (true) {
		file.getline(str, NAME_SIZE, ' ');
		name = convert_to_string(str, strlen(str));

		if (!strcmp(str, "end"))
			break;

		file >> age;
		file.get(); //get '\n'

		newUser = new User(name, age);
		users.push_back(newUser);

		friend_list.push_back(new_vector);
	}

	file.get(); //get '\n'
	file.getline(header, NAME_SIZE, '\n');
	int index, user, type;
	char ch = ' ';
	file.getline(str, NAME_SIZE, ' ');
	file >> index;
	file.get();
	while (true) {

		if (ch == '.') {
			file.get(); //get '\n'
			file.getline(str, NAME_SIZE, ' ');

			if (!strcmp(str, "end"))
				break;
			else if (!strcmp(str, "index")) {
				file >> index;
				file.get();
			}
		}
		file >> user;
		file >> type;
		ch = file.get();

		friendship_type curr_type;
		switch (type) {
		case 0: curr_type = normal; break;
		case 1: curr_type = relative; break;
		case 2: curr_type = bestie; break;
		case 3: curr_type = blocked; break;
		case 4: curr_type = being_blocked; break;
		}
		friend_list[index].push_back(std::pair<int, friendship_type>(user, curr_type));
	}

	file.get(); //get '\n'
	file.getline(header, NAME_SIZE, '\n');
	char c = ' ';
	while (true) {

		if (c == '.')
			break;

		int pos;
		file >> pos;
		free_positions.push(pos);
		file.get(c);
	}

	file.close();
}