#include <iostream>
#include "Stack.hpp"

int main() {

	Stack<int> s;
	s.push(3);
	s.push(4); 
	s.push(7);
	s.push(10);
	s.push(5);
	s.pop(); //5
	s.top(); //10

	return 0;
}