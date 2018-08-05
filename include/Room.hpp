// Room.hpp
#ifndef _ROOM_
#define _ROOM_
#include <iostream>
#include <vector>
#include <random>
#include "Pos.hpp"
#include "Macro.hpp"
using std::vector;

class Room {
public:
	Room(int x, int y);
	int GetWidth() const;
	int GetHeight() const;
	int GetUx() const;
	int GetDx() const;
	int GetLy() const;
	int GetRy() const; 
	Pos FindSpace() const;
	vector<Door>& GetDoor();
private:
	void SetDoor();
private:
	int width_;
	int height_;
	int ux_, dx_, ly_, ry_;
	vector<Door> door_vector_;
};

#endif // !_ROOM_
