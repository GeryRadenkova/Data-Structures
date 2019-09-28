#include<iostream>

struct Node {

	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		next = nullptr;
	}
};

class SinglyLinkedList {

private:
	Node * head;
	Node* tail;

public:
	SinglyLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void AddFirst(int elem) {

		Node* newElem = new Node(elem);
		newElem->next = head;
		head = newElem;
		if (tail == nullptr)
			tail = newElem;
	}

	void AddLast(int elem) {

		Node* newElem = new Node(elem);
		tail->next = newElem;
		tail = newElem;
		if (head == nullptr)
			head = newElem;
	}

	void AddAfterGivenNode(int toSearch, int elem) {

		Node* iter = head;
		while (iter->next != nullptr) {

			if (iter->data == toSearch) {
				Node* newElem = new Node(elem);
				newElem->next = iter->next;
				iter->next = newElem;
				return;
			}
			iter = iter->next;
		}
	}

	void Remove(int elem) {

		Node* iter = head;
		Node* prev = nullptr;

		while (iter != nullptr) {

			if (iter->data == elem) {

				if (iter == head) {

					head = iter->next;
					if (tail == iter)
						tail = nullptr;
					delete iter;
				}
				else if (iter == tail) {

					tail = prev;
					tail->next = nullptr;
					delete iter;
				}
				else {

					prev->next = iter->next;
					delete iter;
				}
				return;
			}

			prev = iter;
			iter = iter->next;
		}
	}

	void Print() {

		Node* iter = head;
		while (iter != nullptr) {
			std::cout << iter->data << " -> ";
			iter = iter->next;
		}
	}

	~SinglyLinkedList() {

		Node* current = head;
		while (current != nullptr) {

			Node* next = current->next;
			delete current;
			current = next;
		}
	}

};

int main() {

	SinglyLinkedList l;
	l.AddFirst(34);
	l.AddFirst(50);
	l.AddFirst(17);
	l.AddFirst(82);
	l.AddLast(60);
	l.AddAfterGivenNode(50, 23);
	l.Print();

	return 0;
}