#pragma once
template <typename T>

class Queue
{
public:
	Queue(int cap = CAP);
	~Queue();
	bool isfull();
	bool isempty();
	int getsize();
	void push(const T &t);
	T pop();
private:
	int capacity, front, rear;
	T* items;
	enum {CAP = 10};
};

template<typename T>
Queue<T>::Queue(int cap) :capacity(cap), front(0), rear(0)
{
	this->items = new T[capacity];
};

template<typename T>
Queue<T>::~Queue()
{
	delete[] items;
};

template<typename T>
bool Queue<T>::isfull()
{
	if ((this->rear + 1) % capacity == this->front) {
		return true;
	}
	return false;
}

template<typename T>
bool Queue<T>::isempty()
{
	if (this->front == this->rear) {
		return true;
	}
	return false;
}

template<typename T>
int Queue<T>::getsize()
{
	return (this->rear - this->front + capacity) % capacity;
}

template<typename T>
void Queue<T>::push(const T& t)
{
	if (this->isfull()) { return; }
	this->items[this->rear] = t;
	this->rear = (this->rear + 1) % capacity;
}

template<typename T>
T Queue<T>::pop() {
	if (this->isempty()) {
		return -1;
	}

	T element = this->items[this->front];
	this->front = (this->front + 1) % capacity;
	return element;
}
