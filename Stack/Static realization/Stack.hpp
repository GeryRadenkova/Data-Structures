#ifndef STACK_HDR
#define STACK_HDR

template<typename T>
class Stack {

private:
	T * arr;
	size_t curSize;
	size_t capacity;

public:
	Stack();
	Stack(const Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& other);
	~Stack();

private:
	void copyFrom(const Stack<T>& other);
	void free();
	void resize(size_t newCap);

public:
	void push(const T& newElem); //add a new element O(1)
	T pop();  //remove an element O(1)
	T top() const;
	bool isEmpty() const;

};

#endif // !STACK_HDR

template<typename T>
Stack<T>::Stack() : curSize(0), capacity(4) {
	arr = new T[capacity];
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
void Stack<T>::copyFrom(const Stack<T>& other) {

	arr = new T[other.capacity];

	for (int i = 0; i < other.curSize; i++) 
		arr[i] = other.arr[i];
	
	curSize = other.curSize;
	capacity = ohter.capacity;
}

template<typename T>
void Stack<T>::free() {
	delete[] arr;
}

template<typename T>
void Stack<T>::resize(size_t newCap) {

	T* temp = arr;
	arr = new T[newCap];
	for (int i = 0; i < curSize; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}

template<typename T>
void Stack<T>::push(const T & newElem) {

	if (curSize >= capacity)
		resize(capacity * 2);

	arr[curSize++] = newElem;
}

template<typename T>
T Stack<T>::pop() {
	
	if (isEmpty())
		throw std::length_error("Already empty!\n");

	return arr[curSize--];
}

template<typename T>
T Stack<T>::top() const {

	if (isEmpty())
		throw std::logic_error("Empty stack.\n");

	return arr[curSize];
}

template<typename T>
bool Stack<T>::isEmpty() const {
	return !curSize;
}
