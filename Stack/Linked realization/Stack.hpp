#ifndef STACK_HDR
#define STACK_HDR

template<typename T>
class Stack {

private:
	struct Node {
		T data;
		Node* next;

		Node(T data) {
			this->data = data;
			next = nullptr;
		}
	};

	Node* topPtr;

	void copyFrom(const Stack<T>& other); //O(n)
	void free();  //O(n)
	
public:
	Stack();
	Stack(const Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& other);
	~Stack();

	void push(const T& newElem); //O(1)
	T pop();  //O(1)
	T top() const;
	bool isEmpty() const;
	void print();

};

#endif // !STACK_HDR

template<typename T>
void Stack<T>::copyFrom(const Stack<T>& other) {

	if (other.isEmpty())
		return;

	Node* iterOther = other.topPtr;

	topPtr = new Node(iterOther->data);
	Node* iterThis = topPtr;

	while(iterOther->next != nullptr) {
		iterOther = iterOther->next;
		iterThis->next = new Node(iterOther->data);
		iterThis = iterThis->next;
	} 
}

template<typename T>
void Stack<T>::free() {

	Node* iter = topPtr;
	while (iter != nullptr) {
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}

template<typename T>
Stack<T>::Stack() : topPtr(nullptr) {

}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) {
	copyFrom(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	free();
}

template<typename T>
void Stack<T>::push(const T& newElem) {

	Node* newNode = new Node(newElem);
	newNode->next = topPtr;
	topPtr = newNode;
}

template<typename T>
T Stack<T>::pop() {
	
	if (isEmpty())
		throw std::logic_error("The stack is empty.\n");
	else {
		T elem = topPtr->data;
		Node* temp = topPtr->next;
		delete topPtr;
		topPtr = temp;
		return elem;
	}
}

template<typename T>
T Stack<T>::top() const {

	if (isEmpty())
		throw std::logic_error("Empty stack\n");

	return topPtr->data;
}

template<typename T>
bool Stack<T>::isEmpty() const {
	return topPtr == nullptr;
}

template<typename T>
void Stack<T>::print() {

	Node* iter = topPtr;
	while (iter->next != nullptr) {
		std::cout << iter->data << " -> ";
		iter = iter->next;
	}
	std::cout << iter->data;
}

