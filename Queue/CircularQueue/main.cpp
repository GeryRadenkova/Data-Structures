#include <iostream>
#include "CircularQueue.hpp"

int main() {

	Queue<int> q;
	q.push(4);
	q.push(12);
	q.push(5);
	q.push(7);
	q.push(9);
	q.print();
	std::cout << std::endl;

	q.pop();
	q.print();
	std::cout << std::endl;

	std::cout << q.peek();
	std::cout << std::endl;

	return 0;
}