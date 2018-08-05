#ifndef _DIREACTION_
#define _DIREACTION_

namespace SimpleNethack {
class Direction {
 public:
  /**
   * @brief Construct a new Direction object
   *
   * @param t
   */
  Direction(int t = 0);

  /**
   * @brief Get the Dx object
   *
   * @return int
   */
  int GetDx() const;

  /**
   * @brief Get the Dy object
   *
   * @return int
   */
  int GetDy() const;

  /**
   * @brief
   *
   * @return Direction&
   */
  Direction& operator++();

  /**
   * @brief
   *
   * @return Direction&
   */
  Direction& operator--();

  /**
   * @brief
   *
   * @param t
   * @return Direction&
   */
  Direction& operator+=(int t);

  /**
   * @brief
   *
   * @param t
   * @return Direction&
   */
  Direction& operator-=(int t);

 private:
  int i_;
  static int dir_[8][2];
};
}  // namespace SimpleNethack

#endif  // !_DIREACTION_