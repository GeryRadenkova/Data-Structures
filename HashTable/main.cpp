#include<iostream>
#include "HashTable.hpp"

int main() {

	HashTable<int> h;

	h.Put("a", 11);
	h.Put("aa", 11);
	h.Put("abc", 22);
	h.Put("bbb", 33);
	h.Get("aa");
	h.Remove("abc");

	return 0;
}