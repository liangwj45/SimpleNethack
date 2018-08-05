// Pos.hpp
#ifndef _POS_
#define _POS_
#include <Windows.h>
#include "Direction.hpp"

struct Pos {
	Pos();
	Pos(int x, int y);
	Pos(const Pos& other);
	Pos& operator=(const Pos& pos);
	bool operator==(const Pos& pos);
	bool operator!=(const Pos& pos);
	Pos operator+(const Direction& dir);
	Pos& operator+=(const Direction& dir);
	static void SetCursor(int x, int y);
	static void SetCursor(Pos pos);
	static int ComputeXY(Pos p1, Pos p2);
	int x;
	int y;
};

struct Door :public Pos {
	Door(int x, int y) : Pos(x, y) {}
};

#endif // !_POS_
