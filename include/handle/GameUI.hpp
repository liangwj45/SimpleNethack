#ifndef _NETHACKUI_
#define _NETHACKUI_

#include <iomanip>
#include <set>
#include <stdexcept>

#include "creature/Player.hpp"
#include "handle/Nethack.hpp"
#include "map/Map.hpp"
#include "map/MapManager.hpp"
#include "position/Direction.hpp"

#include "utility/Utility.hpp"
#include "utility/defines.hpp"

#include "conio.h"

namespace SimpleNethack {

using std::exception;
using std::set;

#define EVENT_X 10
#define EVENT_Y 78
#define EVENT_NUMBER 5

#define STATEX 4
#define STATEY 78

class NethackUI {
 public:
  /**
   * @brief Construct a new NethackUI object
   *
   */
  NethackUI();

  /**
   * @brief Set the Up object
   *
   * 1. Prepare()
   * 2. Initital()
   * 3. GameLoop()
   * 4. CleanUp()
   * 5. Ending()
   *
   */
  void SetUp();

 private:
  /**
   * @brief prepare for the game
   *
   * 1. Preface() get the name of player
   * 2. BasicPrint() print basic frameworks and illustration
   *
   */
  void Prepare();

  /**
   * @brief Game initital
   *
   */
  void Initital();

  /**
   * @brief
   *
   * 1. UpdateData()
   * 2. GetOperation()
   * 3. ExecuteOperation()
   * 4. UpdateView()
   * 5. EnemyRound()
   *
   */
  void GameLoop();

  /**
   * @brief
   *
   */
  void CleanUp();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Ending();

  /**
   * @brief get the name of player
   *
   */
  void Preface();

  /**
   * @brief print basic frameworks and illustration
   *
   */
  void BasicPrint();

  /**
   * @brief update data
   *
   */
  void UpdateData();

  /**
   * @brief Get the Operation object
   *
   * @return char
   */
  char GetOperation();

  /**
   * @brief Execute operation
   * Provided operations:
   * - Move(): WSADQEZC
   * - Rest(): R
   * - Heal(): H
   * - Pick(): J
   * - Attack(): K
   * - OpenDoor(): O
   * - ChangeStair(): U
   * - UseItem(): 12345
   * - Gold(): G
   * - OpenBag(): L
   *
   */
  void ExecuteOperation();

  /**
   * @brief Update view
   *
   */
  void UpdateView();

  /**
   * @brief Round for monster
   *
   */
  void EnemyRound();

 private:
  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Move();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Rest();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Heal();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Pick();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Attack();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void OpenDoor();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void ChangeStair();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void UseItem();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void Gold();

  /**
   * @brief
   *
   * @return true
   * @return false
   */
  void OpenBag();

  /**
   * @brief
   *
   */
  void PrintEvent(string&& message);

  /**
   * @brief
   *
   */
  void PrintEvent();

  /**
   * @brief
   *
   */
  void PrintBag();

 private:
  string name_ = "joker";
  int floor_ = 0;

  int kill_count_ = 0;
  int round_count_ = 0;
  int monster_count_ = 0;

  bool open_bag_ = false;
  bool action_ = false;
  bool stop_singal_ = false;
  bool over_singal_ = false;

  char operation_ = '?';

  shared_ptr<Player> player_;
  shared_ptr<Nethack> nethack_;
  vector<string> event_log_;
};
}  // namespace SimpleNethack
#endif