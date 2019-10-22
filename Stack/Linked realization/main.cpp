#include <iostream>
#include "Stack.hpp"

int main() {

	Stack<int> s;
	s.push(3);
	s.push(7);
	s.push(6);
	s.push(8);
	s.push(2);
	s.print();
	std::cout << std::endl;

	s.pop();
	s.print();
	std::cout << std::endl;

	std::cout << s.top();
	std::cout << std::endl;

	return 0;
}