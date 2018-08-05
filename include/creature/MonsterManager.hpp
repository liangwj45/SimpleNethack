#ifndef _MONSTERMANAGER_
#define _MONSTERMANAGER_

#include "creature/Monster.hpp"

#include "utility/defines.hpp"

namespace SimpleNethack {

class MonsterManager {
 public:
  /**
   * @brief Destroy the Monster Manager object
   *
   */
  ~MonsterManager();

  /**
   * @brief Get the Instance object
   *
   * @return shared_ptr<MonsterManager>
   */
  static shared_ptr<MonsterManager> GetInstance();

  /**
   * @brief Get the Monsters object
   *
   * @param floor
   * @return list<Monster>&
   */
  shared_ptr<list<Monster>> GetMonsters(int floor);

 private:
  /**
   * @brief Construct a new Monster Manager object
   *
   */
  MonsterManager();

 private:
  vector<shared_ptr<list<Monster>>> monsters_;
  static shared_ptr<MonsterManager> instance_;
};

}  // namespace SimpleNethack

#endif