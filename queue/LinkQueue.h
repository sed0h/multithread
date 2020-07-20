#pragma once

template <typename T>
class LinkQueue {
	struct QNode
	{
		QNode* next;
		T data;
	};
	enum {
		Q_Size = 10
	};
private:
	QNode* front;
	QNode* rear;
	size_t items;//current number of items in Queue
	const size_t QSize;

public:
	LinkQueue();
	LinkQueue(size_t sz);
	bool IsEmpty();
	bool IsFull();
	size_t getSize();
	bool EnQueue(const T ndata);
	bool DeQueue(T & ndt);

};

template<typename T>
inline LinkQueue<T>::LinkQueue() :QSize(Q_Size) {
	this->front = this->rear = nullptr;
	items = 0;
}

template<typename T>
inline LinkQueue<T>::LinkQueue(size_t sz) :QSize(sz){
	front = rear = nullptr;
	items = 0;
}

template<typename T>
inline bool LinkQueue<T>::IsEmpty(){
	if (items == 0) {
		return true;
	}
	return false;
}

template<typename T>
inline bool LinkQueue<T>::IsFull(){
	if (items >= QSize) {
		return true;
	}
	return false;
}

template<typename T>
inline size_t LinkQueue<T>::getSize(){
	return items;
}

template<typename T>
inline bool LinkQueue<T>::EnQueue(const T ndata){
	if (!IsFull()) {
		QNode* Nd2add = new QNode;
		Nd2add->data = ndata;
		Nd2add->next = nullptr;
		items++;

		if (front == nullptr){
			front = Nd2add;
		}else{
			rear->next = Nd2add;
		}
		rear = Nd2add;

		return true;
	}
	return false;
}

template<typename T>
inline bool LinkQueue<T>::DeQueue(T& ndt){
	if (front != nullptr) {
		ndt = front->data;
		items--;
	
		if (front == rear) {
			delete front;
			front = rear = nullptr;
		} else {
			QNode* temp = front;
			front = front->next;
			delete temp;
		}
		return true;
	}
	return false;
}


