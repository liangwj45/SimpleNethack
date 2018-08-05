#ifndef _HUMAN_
#define _HUMAN_

#include "creature/Creature.hpp"
#include "item/Bag.hpp"
#include "item/Item.hpp"

#include "utility/Utility.hpp"
#include "utility/defines.hpp"

namespace SimpleNethack {

#define PLAYER '@'

class Player : public Creature {
 public:
  /**
   * @brief Get the Instance object
   *
   * @return shared_ptr<Player>
   */
  static shared_ptr<Player> GetInstance(const Position& pos = Position(2, 2));

  /**
   * @brief
   *
   */
  static void Destroy();

  /**
   * @brief Destroy the Player object
   *
   */
  ~Player();

  /**
   * @brief hp + 1 every 10 round, mp + 1 every 20 round
   *
   */
  virtual void Recover() override;

  /**
   * @brief
   *
   */
  void Heal();

  /**
   * @brief if exp is more than 20 * level, level up
   *
   * @param exp
   * @return true
   * @return false
   */
  bool Grow(int exp);

  /**
   * @brief
   *
   * @param item
   * @return true
   * @return false
   */
  bool PickUp(const Item& item);

  /**
   * @brief
   *
   * @param id
   * @return true
   * @return false
   */
  bool UseItem(int id);

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool IsWeaponed() const;

 public:
  /**
   * @brief Get the Level object
   *
   * @return int
   */
  int GetLevel() const;

  /**
   * @brief Get the Exp object
   *
   * @return int
   */
  int GetExp() const;

  /**
   * @brief Get the Mp object
   *
   * @return int
   */
  int GetMp() const;

  /**
   * @brief Get the Max Mp object
   *
   * @return int
   */
  int GetMaxMp() const;

  /**
   * @brief Get the Weapon object
   *
   * @return std::shared_ptr<Item>
   */
  shared_ptr<Item> GetWeapon() const;

  /**
   * @brief Get the Bag object
   *
   * @return std::shared_ptr<Bag>
   */
  shared_ptr<Bag> GetBag() const;

 private:
  /**
   * @brief Construct a new Player object
   *
   * @param pos
   * @param hp
   * @param atk
   */
  Player(const Position& pos, int hp = 50, int atk = 8);

 private:
  int level_ = 1;
  int exp_ = 0;
  int mp_ = 5;
  int max_mp_ = 5;
  bool weaponed_ = false;
  shared_ptr<Item> weapon_ = nullptr;
  shared_ptr<Bag> bag_ = nullptr;
  static shared_ptr<Player> instance_;
};
}  // namespace SimpleNethack
#endif