#include <iostream>
#include "SocialNetwork.hpp"

int main() {

	SocialNetwork sn;
	sn.create("Pesho", 23);
	sn.create("Ivan", 20);
	sn.create("Gosho", 27);
	sn.link("Pesho", "Ivan");
	sn.link("Ivan", "Gosho");

	return 0;
}