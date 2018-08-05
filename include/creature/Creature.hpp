#ifndef _CREATURE_
#define _CREATURE_

#include "position/Position.hpp"

#include "utility/Utility.hpp"

namespace SimpleNethack {
class Creature {
 public:
  /**
   * @brief Construct a new Creature object
   *
   * @param pos
   * @param hp
   * @param atk
   */
  Creature(const Position& pos, int hp = 16, int atk = 3);

  /**
   * @brief
   *
   */
  virtual void Recover() = 0;

  /**
   * @brief
   *
   * @param dhp
   */
  void Hurt(int dhp);

  /**
   * @brief
   *
   * @param dir
   */
  void Move(const Direction& dir);

  /**
   * @brief Get the Hp object
   *
   * @return int
   */
  int GetHp() const;

  /**
   * @brief Get the Max Hp object
   *
   * @return int
   */
  int GetMaxHp() const;

  /**
   * @brief Get the Atk object
   *
   * @return int
   */
  int GetAtk() const;

  /**
   * @brief Get the Symbol object
   *
   * @return char
   */
  char GetSymbol() const;

  /**
   * @brief Get the Position object
   *
   * @return Position
   */
  Position GetPosition() const;

 protected:
  Position pos_;
  int hp_;
  int max_hp_;
  int atk_;
  char symbol_;
  int recover_count_;
};
}  // namespace SimpleNethack

#endif  // !_CREATURES_
