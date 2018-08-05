// Queue.hpp
#ifndef _QUEUE_
#define _QUEUE_
#include "Pos.hpp"
#define MAX_SIZE 100

class Queue {
public:
	Queue();
	~Queue(); 
	void push(Pos pos);
	void pop(void);
	Pos front(void);
	Pos back(void);
	bool full(void);
	bool empty(void);
	void clear(void);
private:
	Pos* storage_;
	int max_size_;
	int head_;
	int rear_;
};

#endif // !_QUEUE_