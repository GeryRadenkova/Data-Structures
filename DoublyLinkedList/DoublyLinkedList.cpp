#include<iostream>

struct Node {

	int data;
	Node* next;
	Node* prev;

	Node(int data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}
};

class DoublyLinkedList {

private:
	Node* head;
	Node* tail;

public:
	DoublyLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void AddFirst(int elem) {

		Node* newElem = new Node(elem);
		if (head == nullptr) {
			head = newElem;
			tail = newElem;
		}
		else {
			newElem->next = head;
			head->prev = newElem;
			head = newElem;
		}
	}

	void AddLast(int elem) {

		Node* newElem = new Node(elem);
		if (tail == nullptr) {
			head = newElem;
			tail = newElem;
		}
		else {
			newElem->prev = tail;
			tail->next = newElem;
			tail = newElem;
		}
	}

	void AddAfterGivenNode(int toSearch, int elem) {

		Node* iter = head;
		while (iter != nullptr) {

			if (iter->data == toSearch) {
				Node* newElem = new Node(elem);
				newElem->next = iter->next;
				iter->next->prev = newElem;
				iter->next = newElem;
				newElem->prev = iter;
				return;
			}
			iter = iter->next;
		}
	}

	void RemoveFirst() {

		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}

	void RemoveLast() {
		
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}

	void RemoveMiddleNode(int toDelete) {

		Node* iter = head;
		while (iter != nullptr) {

			if (iter->data == toDelete) {
				iter->next->prev = iter->prev;
				iter->prev->next = iter->next;
				delete iter;
				return;
			}
			else 
				iter = iter->next;
		}
	}

	void Print() {

		Node* iter = head;
		while (iter != nullptr) {
			std::cout << iter->data << " <-> ";
			iter = iter->next;
		}
	}

	~DoublyLinkedList() {

		Node* current = head;
		while (current != nullptr) {

			Node* next = current->next;
			delete current;
			current = next;
		}
	}

};

int main() {

	DoublyLinkedList d;
	d.AddLast(4);
	d.AddLast(5);
	d.AddLast(3);
	d.AddLast(7);
	d.AddLast(6);
	d.AddLast(8);
	d.AddLast(10);
	d.AddAfterGivenNode(3, 2);

	d.RemoveMiddleNode(5);

	d.Print();

	return 0;
}