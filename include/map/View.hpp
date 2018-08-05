#ifndef _VIEW_
#define _VIEW_

#include "position/Position.hpp"

namespace SimpleNethack {

#define MAX_MAP_HEIGHT 28
#define MAX_MAP_WIDTH 70

class View {
 public:
  /**
   * @brief Construct a new View object
   *
   * @param pos
   * @param range
   */
  View(const Position& pos = Position(2, 2));

  /**
   * @brief Construct a new View object
   *
   * @param other
   */
  View(const View& other);

  /**
   * @brief Get the View object
   *
   * @param pos
   * @return char
   */
  bool GetView(const Position& pos) const;

  /**
   * @brief
   *
   * @param pos
   */
  void UpdateView(const Position& pos);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool& operator[](const Position& pos);

  /**
   * @brief
   *
   * @param pos
   * @return true
   * @return false
   */
  bool operator()(const Position& pos);

 private:
  bool view_[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
};
}  // namespace SimpleNethack
#endif