// Monster.hpp
#ifndef _MONSTER_
#define _MONSTER_
	
#include "Creature.hpp"
#include <random>

class Monster : public Creature {
public:
	Monster() : Creature() {
		std::random_device e;
		std::uniform_int_distribution<int> r('M', 'N');
		symbol_ = r(e);
	}
	Monster(const Pos& pos, int floor = 0) :Creature(pos, floor) {
		std::random_device e;
		std::uniform_int_distribution<int> r('M', 'N');
		symbol_ = r(e);
	}
	Monster(const Pos& pos, int floor, int atk, int hp) :Creature(pos, floor, atk) {
		std::random_device e;
		std::uniform_int_distribution<int> r('M', 'N');
		symbol_ = r(e);
		hp_ = hp;
	
	}
	void Recover() {
		recover_count_++;
		if (recover_count_ % 5 == 0 && hp_ < max_hp_) hp_++;
		if (recover_count_ % 40 == 0) max_hp_++;
		if (recover_count_ % 60 == 0) {
			atk_++;
			recover_count_ = 0;
		}
	}
};

#endif // !_MONSTER_