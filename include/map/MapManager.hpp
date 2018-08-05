#ifndef _MAPMANAGER_
#define _MAPMANAGER_

#include "map/Map.hpp"
#include "position/Position.hpp"

#include "utility/defines.hpp"

namespace SimpleNethack {
class MapManager {
 public:
  /**
   * @brief Destroy the Map Manager object
   *
   */
  ~MapManager();

  /**
   * @brief Get the Instance object
   *
   * @return shared_ptr<MapManager>
   */
  static shared_ptr<MapManager> GetInstance();

  /**
   * @brief
   *
   */
  void clear();

  /**
   * @brief Get the Map object
   *
   * @param id
   * @return shared_ptr<Map>
   */
  shared_ptr<Map> GetMap(int floor, const Position& pos = Position(2, 2));

 private:
  /**
   * @brief Construct a new Map Manager object
   *
   */
  MapManager();

 private:
  vector<shared_ptr<Map>> maps_;
  static shared_ptr<MapManager> instance_;
};
}  // namespace SimpleNethack

#endif