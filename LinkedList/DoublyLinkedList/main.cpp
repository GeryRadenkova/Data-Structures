#include<iostream>
#include "DoublyLinkedList.hpp"

int main() {

	LinkedList<int> d;
	d.PushBack(4);
	d.PushBack(5);
	d.PushBack(3);
	d.PushBack(7);
	d.PushBack(6);
	d.PushBack(8);
	d.PushBack(10);
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 7 <-> 6 <-> 8 <-> 10

	d.Remove(6);
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 7 <-> 8 <-> 10

	d.InsertAfter(3, 2);
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 2 <-> 7 <-> 8 <-> 10

	d.PopBack();
	d.Print();
	std::cout << std::endl;
	// result: 4 <-> 5 <-> 3 <-> 2 <-> 7 <-> 8

	d.PopFront();
	d.Print();
	std::cout << std::endl;
	// result: 5 <-> 3 <-> 2 <-> 7 <-> 8

	return 0;
}