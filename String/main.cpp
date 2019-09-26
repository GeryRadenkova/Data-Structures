#include<iostream>
#include"String.h"

int main() {

	String str("abcedfgh");
	std::cout << str.SubString(2) << std::endl;
	// result: cedfgh

	std::cout << str.SubString(1, 5) << std::endl;
	// result: bcedf

	String str2("ced");
	std::cout << str.IndexOf(str2, 0) << std::endl;
	// result: 2

	str += str2;
	std::cout << str << std::endl;
	// result: abcedfghced

	bool res = str == str2;
	std::cout << res << std::endl;
	// result: false

	return 0;
}