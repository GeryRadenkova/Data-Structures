#include <iostream>
#include "SocialNetwork.hpp"

int main() {

	SocialNetwork sn;
	sn.create("Pesho", 23);
	sn.create("Ivan", 20);
	sn.create("Ivan", 22);
	sn.create("Gosho", 27);
	sn.link("Pesho", "Ivan", relative);
	sn.link("Ivan", "Gosho");
	sn.find("Pesho");

	sn.delink("Pesho", "Ivan");

	return 0;
}