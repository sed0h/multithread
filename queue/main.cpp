//#include <iostream>
//#include <cctype>
//#include "Queue.h"
//using std::cout;
//
//int main(int argc, char* argv[]) {
//	/*int size = 10;*/
//	Queue<int>q(10);
//	int a = 10;
//	q.push(a);
//	q.push(9);
//	q.push(8);
//
//	cout << "pop: " << q.pop() << q.pop() << q.pop() << "\n";
//
//	return 0;
//}

#include "LinkQueue.h"
#include <iostream>
using std::cout;

int main() {
	LinkQueue<double>q(10);
	q.EnQueue(9.8);
	q.EnQueue(8.8);
	q.EnQueue(7.7);

	double v = 0;
	size_t sz = q.getSize();
	for (size_t i = 0; i < sz; i++){
		q.DeQueue(v);
		cout << v << "\n";
	}
	
	return 0;
}