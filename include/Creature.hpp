// Creature.hpp
#ifndef _CREATURE_
#define _CREATURE_

#include <random>
#include "Map.hpp"
#include "Pos.hpp"
#include "Direction.hpp"

class Creature {
public:
	Creature();
	Creature(const Pos& t_pos, int t_floor = 0);
	Creature(const Pos& t_pos, int t_floor, int t_atk);
	virtual void Recover() = 0; // Recover
	void Hurt(int dhp);
	void Move(Direction dir);
	Pos  GetPos() const;
	void SetPos(Pos pos);
	int  GetAtk() const;
	int  GetFloor() const;
	int  GetHp() const;
	int  GetMaxHp() const;
	char GetSymbol() const;
	void ChangeFloor(int t);
protected:
	Pos pos_;
	int atk_;
	int floor_;
	int hp_;
	int max_hp_;
	char symbol_;
	int recover_count_;
};

#endif // !_CREATURES_
