// Queue.cpp

#include "Queue.hpp"

Queue::Queue() {
	storage_ = new Pos[MAX_SIZE + 1];
	max_size_ = MAX_SIZE + 1;
	head_ = 0;
	rear_ = 0;
}

Queue::~Queue() {

	delete[]storage_;
}

void Queue::push(Pos pos) {
	if (rear_ < max_size_ - 1) {
		storage_[rear_] = pos;
		rear_++;
	}
}

void Queue::pop(void) {
	if (rear_) {
		for (int i = head_; i < rear_ - 1; i++) {
			storage_[i] = storage_[i + 1];
		}
		rear_--;
	}
}

Pos Queue::front(void) {
	if (rear_) return storage_[head_];
}

Pos Queue::back(void) {
	if (rear_) return storage_[rear_ - 1];
}

bool Queue::full(void) {
	return rear_ == MAX_SIZE;
}

bool Queue::empty(void) {
	return rear_ == 0;
}

void Queue::clear(void) {
	head_ = 0;
	rear_ = 0;
}