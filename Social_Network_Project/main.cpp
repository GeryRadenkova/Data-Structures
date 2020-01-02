#include <iostream>
#include "SocialNetwork.hpp"

void menu(SocialNetwork& sn);

int main() {

	SocialNetwork sn;
	menu(sn);


	/*SocialNetwork sn;
	sn.create("Pesho", 23);
	sn.create("Ivan", 20);
	sn.create("Gosho", 27);
	sn.create("Ana", 21);
	sn.create("Kiro", 22);
	sn.create("Geri", 21);
	sn.create("Gabi", 30);
	sn.create("Niki", 25);

	sn.link("Pesho", "Gosho");
	sn.link("Pesho", "Ana", relative);
	sn.link("Pesho", "Geri");
	sn.link("Pesho", "Niki", bestie);
	sn.link("Ivan", "Gosho");
	sn.link("Ivan", "Ana");
	sn.link("Ivan", "Kiro", bestie);
	sn.link("Ivan", "Gabi");
	sn.link("Gosho", "Pesho");
	sn.link("Gosho", "Ivan");
	sn.link("Gosho", "Ana",relative);
	sn.link("Gosho", "Kiro");
	sn.link("Gosho", "Geri", bestie);
	sn.link("Gosho", "Gabi", bestie);
	sn.link("Gosho", "Niki");
	sn.link("Ana", "Geri");
	sn.link("Niki", "Gabi");
	menu(sn);*/


	return 0;
}

void menu(SocialNetwork& sn) {

	std::string command;
	std::string name;
	std::string name1;
	std::string friendship;
	int age;
	int type;

	while (true) {

		std::cout << ">";
		std::getline(std::cin, command, ' ');

		if (command == "CREATE") {
			std::getline(std::cin, name, ' ');
			std::cin >> age;

			if (sn.create(name, age))
				std::cout << "User " << name << " created.\n";
			else
				std::cout << "FAIL: " << name << " already exists.\n";

			std::cin.get();//get '\n'
		}
		else if (command == "LINK") {

			std::getline(std::cin, name, ' ');
			std::getline(std::cin, name1, ' ');
			std::getline(std::cin, friendship);
			
			if (friendship == "normal")
				type = 0;
			else if (friendship == "relative")
				type = 1;
			else if (friendship == "bestie")
				type = 2;
			
			friendship_type ftype;
			switch (type) {
			case 0: ftype = normal; break;
			case 1: ftype = relative; break;
			case 2: ftype = bestie; break;
			default: std::cout << "Invalid friendship type.\n";
			}

			if (sn.link(name, name1, ftype) == 1)
				std::cout << "No such user.\n";
			else if (sn.link(name, name1, ftype) == 2)
				std::cout << "User " << name << " is banned.\n";
			else if (sn.link(name, name1, ftype) == 3) {
				if(type == 0)
					std::cout << "User " << name << " and " << name1 << " are normal now.\n";
				else if(type ==1)
					std::cout << "User " << name << " and " << name1 << " are relative now.\n";
				else if(type ==2)
					std::cout << "User " << name << " and " << name1 << " are bestie now.\n";
			}
		}
		else if (command == "FIND") {

			std::getline(std::cin, name);
			if (!sn.find(name))
				std::cout << "No such user.\n";
		}
		else if (command == "BAN") {

			std::getline(std::cin, name, ' ');
			std::getline(std::cin, name1);

			if (sn.ban(name, name1))
				std::cout << "User " << name1 << " is now banned by " << name << std::endl;
			else
				std::cout << "No such user.\n";
		}
		else if (command == "DELETE") {

			std::getline(std::cin, name);
			if (sn.remove(name))
				std::cout << "User " << name << " has been deleted.\n";
			else
				std::cout << "No such user.\n";
		}
		else if (command == "DELINK") {

			std::getline(std::cin, name, ' ');
			std::getline(std::cin, name1);

			if (sn.delink(name, name1))
				std::cout << "Users " << name << " and " << name1 << " are delinked now.\n";
			else
				std::cout << "No such user.\n";
		}
		else if (command == "RECOMMEND") {

			std::getline(std::cin, name);
			sn.recommend(name);

			std::cout << std::endl;
		}
		else if (command == "SAVETOFILE") {
			sn.store_in_file();
		}
		else if (command == "READFROMFILE") {
			sn.load_from_file();
		}
		else if (command == "EXIT")
			break;
		else {
			std::cout << "Wrong input!\nTry again.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}