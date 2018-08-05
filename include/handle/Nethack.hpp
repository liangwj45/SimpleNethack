#ifndef _NETHACK_
#define _NETHACK_

#include "creature/Monster.hpp"
#include "creature/MonsterManager.hpp"
#include "creature/Player.hpp"
#include "map/Map.hpp"
#include "map/MapManager.hpp"
#include "map/View.hpp"
#include "map/ViewManager.hpp"

#include "utility/Utility.hpp"
#include "utility/defines.hpp"

namespace SimpleNethack {

#define VISION_RANGE 3

#define PLAYER_COLOR 14
#define LIGHT_COLOR 15
#define MONSTER_COLOR 12

#define MONSTER_INITIAL_NUMBER 10
#define CREATE_MONSTER_ROUND 20

#define ITEM_NUMBER 30

class Nethack {
 public:
  /**
   * @brief Destroy the Nethack object
   *
   */
  ~Nethack();

  /**
   * @brief Get the Instance object
   *
   * @return shared_ptr<Nethack>
   */
  static shared_ptr<Nethack> GetInstance();

  /**
   * @brief
   *
   */
  static void Destroy();

  /**
   * @brief game initial
   * 1. init floor
   * 2. init see_monster
   * 3. init player
   * 4. init map
   * 5. init view
   * 6. init monsters (and create monsters)
   *
   */
  void Initial();

  /**
   * @brief Create a Monster object
   *
   */
  void CreateMonster();

 public:
  /**
   * @brief update view
   * 1. HideVision(): hide vision out of view range
   * 2. PrintCenter(): print player
   * 3. PrintVision(): print vision among view range
   * 4. UpdateMonster(): print monsters
   *
   */
  void UpdateView();

  /**
   * @brief
   *
   */
  void UpdateMonster();

 private:
  /**
   * @brief
   *
   */
  void HideVision();

  /**
   * @brief
   *
   */
  void PrintCenter();

  /**
   * @brief
   *
   */
  void PrintVision();

 public:
  /**
   * @brief Monster actions
   * 1. MonsterRecover(): growing
   * 1. AttackPlayer(): attack player
   * 2. GetCloser(): get closer to player
   * 3. RandomMove(): random move
   *
   */
  void MonsterAction();

 private:
  /**
   * @brief
   *
   */
  void MonsterRecover(Monster& monster);

  /**
   * @brief
   *
   */
  void AttackPlayer(const Monster& monster);

  /**
   * @brief
   *
   */
  void GetCloser(Monster& monster);

  /**
   * @brief
   *
   */
  void RandomMove(Monster& monster);

 public:
  /**
   * @brief
   *
   * @param dir
   * @return true
   * @return false
   */
  bool Move(const Direction& dir);

 public:
  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool Rest();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool Heal();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool Pick(Item& item);

  /**
   * @brief
   *
   * @param kill_signal
   * @return true
   * @return false
   */
  bool Attack(bool& kill_signal);

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool OpenDoor();

  /**
   * @brief Change stair
   * 1. CleanMap()
   * 2. Update data
   * 3. PrintMap()
   * 4. UpdateView()
   *
   * @param floor
   * @return true
   * @return false
   */
  bool ChangeStair(int& floor);

  /**
   * @brief
   *
   * @param id
   * @return true
   * @return false
   */
  bool UseItem(int id, Item& item);

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  bool SeeMonster();

 private:
  /**
   * @brief Construct a new Nethack object
   *
   */
  Nethack();

  /**
   * @brief Check if the position has a monster
   *
   * @param pos
   * @return true
   * @return false
   */
  bool IsMonster(const Position& pos);

  /**
   * @brief
   *
   * @param mpos
   * @return true
   * @return false
   */
  bool CanAttack(const Position& mpos);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool CanSee(const Position& pos);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool CanMove(const Position& pos);

  /**
   * @brief Get the Direction object
   *
   * @param pos
   * @return Direction
   */
  Direction GetDirection(const Position& pos);

  /**
   * @brief
   *
   * @param pos
   * @return Direction
   */
  Direction RandomDirection(const Position& pos);

  /**
   * @brief Get the Monster object
   *
   * @param pos
   * @return Monster&
   */
  Monster& GetMonster(const Position& pos);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  inline bool InMap(const Position& pos);

  /**
   * @brief Get the Map Char object
   *
   * @param pos
   * @return char
   */
  inline char GetMapChar(const Position& pos);

  /**
   * @brief
   *
   */
  void CleanMap();

  /**
   * @brief
   *
   */
  void PrintMap();

 private:
  int floor_ = 0;
  bool see_monster_ = false;

  Direction direction_;

  shared_ptr<Player> player_;
  shared_ptr<Map> map_;
  shared_ptr<View> view_;
  shared_ptr<list<Monster>> monsters_;

  static shared_ptr<Nethack> instance_;
};
}  // namespace SimpleNethack
#endif