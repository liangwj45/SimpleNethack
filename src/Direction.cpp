// Direction.cpp
#include "Direction.hpp"

Direction::Direction() :Direction(0) {}

Direction::Direction(int t) {
	i_ = t % 8;
	dx_ = dir_[i_][0];
	dy_ = dir_[i_][1];
}

Direction::Direction(int dx, int dy) :dx_(dx), dy_(dy) {}

Direction& Direction::operator++() {
	i_ = (i_ + 1) % 8;
	dx_ = dir_[i_][0];
	dy_ = dir_[i_][1];
	return *this;
}

Direction& Direction::operator--() {
	i_ = (i_ + 7) % 8;
	dx_ = dir_[i_][0];
	dy_ = dir_[i_][1];
	return *this;
}

Direction& Direction::operator+=(int t) {
	i_ = (i_ + t) % 8;
	dx_ = dir_[i_][0];
	dy_ = dir_[i_][1];
	return *this;
}

Direction& Direction::operator-=(int t) {
	t %= 8;
	i_ = (i_ - t + 8) % 8;
	dx_ = dir_[i_][0];
	dy_ = dir_[i_][1];
	return *this;
}