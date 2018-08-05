// Pos.cpp
#include "Pos.hpp"

Pos::Pos() :x(0), y(0) {}

Pos::Pos(int x, int y) :x(x), y(y) {}

Pos::Pos(const Pos& other) :x(other.x), y(other.y) {}

Pos& Pos::operator=(const Pos& pos) {
	x = pos.x;
	y = pos.y;
	return *this;
}

bool Pos::operator==(const Pos& pos) {
	return (x == pos.x && y == pos.y);
}

bool Pos::operator!=(const Pos& pos) {
	return !(*this == pos);
}

Pos Pos::operator+(const Direction& dir) {
	Pos pos(x + dir.dx_, y + dir.dy_);
	return pos;
}

Pos& Pos::operator+=(const Direction& dir) {
	x += dir.dx_;
	y += dir.dy_;
	return *this;
}

void Pos::SetCursor(int x, int y) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
}

void Pos::SetCursor(Pos pos) {
	SetCursor(pos.x, pos.y);
}

int Pos::ComputeXY(Pos p1, Pos p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}