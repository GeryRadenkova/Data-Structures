#ifndef CIRCULARQUEUE_HDR
#define CIRCULARQUEUE_HDR

template<typename T>
class Queue {
private:
	T * arr;
	int capacity;
	int count;

	int front;
	int rear;

	void resize();
	void copyFrom(const Queue<T>& other);
	void free();

public:
	Queue();
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);
	~Queue();

	bool isEmpty();
	void push(T elem);
	T pop();
	T& peek();
	void print();
};

template <typename T>
void Queue<T>::resize() {

	T* temp = new T[capacity * 2];
	for (int i = 0; i < capacity; ++i)
		temp[i] = pop();

	front = 0;
	rear = capacity;
	count = capacity;
	capacity *= 2;
	delete[] arr;
	arr = temp;
}

template <typename T>
void Queue<T>::copyFrom(const Queue<T>& other) {

	arr = new T[other.capacity];
	for (int i = 0; i < other.count; ++i)
		arr[i] = other.arr[i];

	count = other.count;
	capacity = other.capacity;
	front = other.front;
	rear = other.rear;
}

template <typename  T>
void Queue<T>::free() {
	delete[] arr;
	count = capacity = 0;
}

template <typename T>
Queue<T>::Queue() {
	arr = new T[4];
	capacity = 4;
	count = 0;
	front = 0;
	rear = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
	CopyFrom(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {

	if (this != &other) {
		Free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
Queue<T>::~Queue() {
	free();
}

template <typename T>
bool Queue<T>::isEmpty() {
	return count == 0;
}

template <typename T>
void Queue<T>::push(T elem) {

	if (count == capacity)
		resize();

	arr[rear] = elem;
	(rear += 1) %= capacity;
	count++;
}

template <typename T>
T Queue<T>::pop() {

	if (count == 0)
		throw "Queue is empty";

	T elToReturn = arr[front];
	count--;
	(front += 1) %= capacity;
	return elToReturn;
}

template <typename T>
T& Queue<T>::peek() {

	if (isEmpty())
		throw std::logic_error("empty queue");

	return arr[front];
}

template<typename T>
void Queue<T>::print() {

	for (int i = front; i < rear - 1; i++) {
		std::cout << arr[i] << " - ";
	}
	std::cout << arr[rear - 1];
}

#endif // !CIRCULARQUEUE_HDR