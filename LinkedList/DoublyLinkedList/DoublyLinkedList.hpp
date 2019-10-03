#include<iostream>

template<typename T>
struct Node {

	T data;
	Node* next;
	Node* prev;

	Node(T data) {
		this->data = data;
		next = nullptr;
		prev = nullptr;
	}
};

template<typename T>
class DoublyLinkedList {

private:
	Node<T>* head;
	Node<T>* tail;

public:
	DoublyLinkedList() {
		head = nullptr;
		tail = nullptr;
	}

	void AddFirst(T elem) {

		Node<T>* newElem = new Node<T>(elem);
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

	void AddLast(T elem) {

		Node<T>* newElem = new Node<T>(elem);
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

	void AddAfterGivenNode(T toSearch, T elem) {

		Node<T>* iter = Search(toSearch);

		if (iter == nullptr)
			return;

		if (iter == head)
			AddFirst(elem);
		else if (iter == tail)
			AddLast(elem);
		else {
			Node<T>* newElem = new Node<T>(elem);
			newElem->next = iter->next;
			iter->next->prev = newElem;
			iter->next = newElem;
			newElem->prev = iter;
		}
	}

	Node<T>* Search(T toSearch) {

		Node<T>* iter = head;

		while (iter != nullptr) {
			if (iter->data == toSearch)
				return iter;
			else
				iter = iter->next;
		}

		return nullptr;
	}

	void RemoveFirst() {

		if (head == nullptr)
			return;
		else if (head == tail) 
			delete head;
		else {
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
	}

	void RemoveLast() {
		
		if (tail == nullptr)
			return;
		else if (head == tail)
			delete tail;
		else {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
	}

	void RemoveNodeByData(T toDelete) {

		Node<T>* iter = Search(toDelete);

		if (iter == nullptr)
			return;
	
		if (iter == head)
			RemoveFirst();
		else if (iter == tail)
			RemoveLast();
		else {
			iter->next->prev = iter->prev;
			iter->prev->next = iter->next;
			delete iter;
		}
	}

	void Print() {

		Node<T>* iter = head;
		while (iter != nullptr) {
			std::cout << iter->data << " <-> ";
			iter = iter->next;
		}
	}

	~DoublyLinkedList() {

		Node<T>* current = head;
		while (current != nullptr) {

			Node<T>* next = current->next;
			delete current;
			current = next;
		}
	}

};