#include "creature/Creature.hpp"

namespace SimpleNethack {

Creature::Creature(const Position& pos, int hp, int atk)
    : pos_(pos),
      hp_(hp),
      max_hp_(hp),
      atk_(atk),
      symbol_('?'),
      recover_count_(0) {}

void Creature::Hurt(int dhp) {
  hp_ -= dhp;
  hp_ = hp_ < 0 ? 0 : hp_;
}

void Creature::Move(const Direction& dir) { pos_ += dir; }

Position Creature::GetPosition() const { return pos_; }

int Creature::GetHp() const { return hp_; }

int Creature::GetMaxHp() const { return max_hp_; }

int Creature::GetAtk() const { return atk_; }

char Creature::GetSymbol() const { return symbol_; }

}  // namespace SimpleNethack