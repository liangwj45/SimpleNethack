// Creature.cpp
#include "Creature.hpp"

Creature::Creature()
	: pos_(0, 0),
	atk_(3),
	floor_(0),
	hp_(16),
	max_hp_(16),
	symbol_('?'),
	recover_count_(0) {}

Creature::Creature(const Pos& t_pos, int t_floor)
	: pos_(t_pos),
	floor_(0),
	atk_(3),
	hp_(16),
	max_hp_(16),
	symbol_('?'),
	recover_count_(0) {}

Creature::Creature(const Pos& t_pos, int t_floor, int t_atk)
	: pos_(t_pos),
	floor_(t_floor),
	atk_(t_atk),
	hp_(16),
	max_hp_(16),
	symbol_('?'),
	recover_count_(0) {}

Pos  Creature::GetPos() const {
	return pos_;
}

void Creature::SetPos(Pos pos) {
	pos_.x = pos.x;
	pos_.y = pos.y;
}

int  Creature::GetAtk() const {
	return atk_;
}

int  Creature::GetFloor() const {
	return floor_;
}

void Creature::ChangeFloor(int t) {
	floor_ += t;
}

int  Creature::GetHp() const {
	return hp_;
}

int  Creature::GetMaxHp() const {
	return max_hp_;
}

char Creature::GetSymbol() const {
	return symbol_;
}

void Creature::Hurt(int dhp) {
	hp_ -= dhp;
	if (hp_ <= 0) {
		hp_ = 0;
	}
}

void Creature::Move(Direction dir) {
	pos_ += dir;
}