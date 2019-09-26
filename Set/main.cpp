#include<iostream>
#include"Set.hpp"

int main() {

	Set<int> set1;
	set1.Add(3);
	set1.Add(18);
	set1.Add(5);
	set1.Add(9);
	set1.Add(15);
	// result: {3, 18, 5, 9, 15}

	Set<int> set2;
	set2.Add(2);
	set2.Add(18);
	set2.Add(9);
	set2.Add(7);
	set2.Add(10);
	// result: {2, 18, 9, 7, 10}

	Set<int> set3 = Union(set1, set2);
	set3.Print();
	std::cout << std::endl;
	// result: {3, 18, 5, 9, 15, 2, 7, 10}

	Set<int> set4 = Intersection(set1, set2);
	set4.Print();
	std::cout << std::endl;
	// result: {18 , 9}

	Set<int> set5 = SetDifference(set3, set4);
	set5.Print();
	std::cout << std::endl;
	// result: {3, 5, 15, 2, 7, 10}

	return 0;
}