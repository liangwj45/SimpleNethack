// Room.cpp
#include "Room.hpp"

Room::Room(int x, int y) {
	std::random_device e;
	std::uniform_int_distribution<int> randwidth(ROOM_WIDTH_MIN, ROOM_MAX_WIDTH);
	std::uniform_int_distribution<int> randheigth(ROOM_HEIGTH_MIN, ROOM_MAX_HEIGTH);
	width_ = randwidth(e);
	height_ = randheigth(e);
	std::uniform_int_distribution<int> randx(x, x + ROOM_MAX_HEIGTH - height_);
	std::uniform_int_distribution<int> randy(y, y + ROOM_MAX_WIDTH - width_);
	ux_ = randx(e);
	dx_ = ux_ + height_ - 1;
	ly_ = randy(e);
	ry_ = ly_ + width_ - 1;
	SetDoor();
}

void Room::SetDoor() {
	std::random_device e;
	std::uniform_int_distribution<int> randx(ux_ + 1, dx_ - 1);
	std::uniform_int_distribution<int> randy(ly_ + 1, ry_ - 1);
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			door_vector_.push_back(Door(ux_, randy(e)));
			break;
		case 1:
			door_vector_.push_back(Door(randx(e), ry_));
			break;
		case 2:
			door_vector_.push_back(Door(dx_, randy(e)));
			break;
		case 3:
			door_vector_.push_back(Door(randx(e), ly_));
			break;
		default:
			break;
		}
	}
}

Pos Room::FindSpace() const {
	std::random_device e;
	std::uniform_int_distribution<int> rx(ux_ + 1, dx_ - 1);
	std::uniform_int_distribution<int> ry(ly_ + 1, ry_ - 1);
	return Pos(rx(e), ry(e));
}

int Room::GetWidth() const {
	return width_;
}

int Room::GetHeight() const {
	return height_;
}

int Room::GetUx() const {
	return ux_;
}

int Room::GetDx() const {
	return dx_;
}

int Room::GetLy() const {
	return ly_;
}

int Room::GetRy() const {
	return ry_;
}

vector<Door>& Room::GetDoor() {
	return door_vector_;
}