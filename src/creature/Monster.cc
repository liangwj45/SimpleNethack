#include "creature/Monster.hpp"

namespace SimpleNethack {
Monster::Monster(const Position& pos, int hp, int atk)
    : Creature(pos, hp, atk) {
  // TO: more types of monster
  symbol_ = rand('M', 'N');
}

void Monster::Recover() {
  recover_count_++;
  if (recover_count_ % 5 == 0 && hp_ < max_hp_) hp_++;
  if (recover_count_ % 40 == 0) max_hp_++;
  if (recover_count_ % 60 == 0) atk_++;
  if (recover_count_ == 60) recover_count_ = 0;
}
}  // namespace SimpleNethack