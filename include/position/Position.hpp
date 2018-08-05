#ifndef _POSITION_
#define _POSITION_

#include "position/Direction.hpp"

namespace SimpleNethack {

struct Position {
  /**
   * @brief Construct a new Position object
   *
   * @param x
   * @param y
   */
  Position(int x = 0, int y = 0);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool operator==(const Position& pos) const;

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool operator!=(const Position& pos) const;

  /**
   * @brief
   *
   * @param dir
   * @return Position
   */
  Position operator+(const Direction& dir) const;

  /**
   * @brief
   *
   * @param dir
   * @return Position&
   */
  Position& operator+=(const Direction& dir);

  int x = 0;
  int y = 0;
};
}  // namespace SimpleNethack
#endif  // !_POS_
