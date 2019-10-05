#ifndef DOUBLYLINKEDLIST_HDR
#define DOUBLYLINKEDLIST_HDR

#include<iostream>

template<typename T>
class LinkedList {

private:
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

	Node* head;
	Node* tail;

	void CopyFrom(const LinkedList& other);
	void Free();

public:
	LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList& operator=(const LinkedList& other);
	~LinkedList();

	void PushFront(T elem); // Insert new element in the begining of the list. Time complexity: O(1)
	void PushBack(T elem); // Insert new element at the end of the list. Time complexity: O(1)
	void PopFront(); // Remove the first element. Time complexity: O(1)
	void PopBack(); // Remove the last element. Time complexity: O(1)
	void InsertAfter(T toSearch, T elem); // Insert an element after a given element.
	void Remove(T toDelete); // Remove random element from the list.
	bool isEmpty() const;
	void Print() const;

	Node* Search(T toSearch) {

		Node* iter = head;

		while (iter != nullptr) {
			if (iter->data == toSearch)
				return iter;
			else
				iter = iter->next;
		}

		return nullptr;
	}

};

template<typename T>
void LinkedList<T>::CopyFrom(const LinkedList& other) {

	Node* iter = other.head;
	while (iter != nullptr) {
		PushBack(iter->data);
		iter = iter->next;
	}
}

template<typename T>
void LinkedList<T>::Free() {

	Node* toDelete = head;
	while (toDelete != nullptr) {
		Node* next = toDelete->next;
		delete toDelete;
		toDelete = next;
	}
}

template<typename T>
LinkedList<T>::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
	CopyFrom(other);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {

	if (this != other) {
		Free();
		CopyFrom(other);
	}

	return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Free();
}

template<typename T>
void LinkedList<T>::PushFront(T elem) {

	Node* newElem = new Node(elem);

	if (isEmpty())
		head = tail = newElem;
	else {
		newElem->next = head;
		head->prev = newElem;
		head = newElem;
	}
}

template<typename T>
void LinkedList<T>::PushBack(T elem) {

	Node* newElem = new Node(elem);

	if (isEmpty())
		head = tail = newElem;
	else {
		newElem->prev = tail;
		tail->next = newElem;
		tail = newElem;
	}
}

template<typename T>
void LinkedList<T>::PopFront() {

	if (isEmpty())
		throw std::logic_error("The list is empty.\n");
	else if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
	}
}

template<typename T>
void LinkedList<T>::PopBack() {

	if (isEmpty())
		throw std::logic_error("The list is empty.\n");
	else if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(T toSearch, T elem) {

	Node* iter = Search(toSearch);

	if (isEmpty())
		return;

	if (iter == tail)
		PushBack(elem);
	else {
		Node* newElem = new Node(elem);
		newElem->next = iter->next;
		iter->next->prev = newElem;
		iter->next = newElem;
		newElem->prev = iter;
	}
}

template<typename T>
void LinkedList<T>::Remove(T toDelete) {

	Node* iter = Search(toDelete);

	if (isEmpty())
		return;

	if (iter == head)
		PopFront();
	else if (iter == tail)
		PopBack();
	else {
		iter->next->prev = iter->prev;
		iter->prev->next = iter->next;
		delete iter;
	}
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
	return head == nullptr;
}

template<typename T>
void LinkedList<T>::Print() const {

	Node* iter = head;
	while (iter->next != nullptr) {
		std::cout << iter->data << " <-> ";
		iter = iter->next;
	}
	std::cout << iter->data;
}

#endif // !DOUBLYLINKEDLIST_HDR
