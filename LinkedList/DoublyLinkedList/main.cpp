#include<iostream>
#include "DoublyLinkedList.hpp"

int main() {

	DoublyLinkedList<int> d;
	d.AddLast(4);
	d.AddLast(5);
	d.AddLast(3);
	d.AddLast(7);
	d.AddLast(6);
	d.AddLast(8);
	d.AddLast(10);
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 7 <-> 6 <-> 8 <-> 10

	d.AddAfterGivenNode(3, 2);
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 2 <-> 7 <-> 6 <-> 8 <-> 10

	d.RemoveLast();
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 2 <-> 7 <-> 6 <-> 8

	d.RemoveFirst();
	d.Print();
	std::cout << std::endl;
	// result: 5 <-> 3 <-> 2 <-> 7 <-> 6 <-> 8

	return 0;
}