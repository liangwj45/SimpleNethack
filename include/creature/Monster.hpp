#ifndef _MONSTER_
#define _MONSTER_

#include "creature/Creature.hpp"

#include "utility/Utility.hpp"

namespace SimpleNethack {
class Monster : public Creature {
 public:
  /**
   * @brief Construct a new Monster object
   *
   * @param pos
   * @param hp
   * @param atk
   */
  Monster(const Position& pos, int hp = 16, int atk = 3);

  /**
   * @brief recover
   *
   */
  void Recover();
};
}  // namespace SimpleNethack
#endif