#include<iostream>
#include"DynamicArray.hpp"

int main() {

	DynamicArray<int> arr;
	arr.PushBack(22);
	arr.PushBack(34);
	arr.PushBack(52);
	arr.PushBack(7);
	// result: [22, 34, 52, 7]
	
	arr.InsertAt(2, 18);
	// result: [22, 34, 18, 52, 7]
	
	arr.RemoveAt(1);
	// result: [22, 18, 52, 7]
	
	arr.PopBack();
	// result: [22, 18, 52]

	arr.getSize();
	// result: 3

	return 0;
}