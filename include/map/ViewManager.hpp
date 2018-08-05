#ifndef _VIEWMANAGER_
#define _VIEWMANAGER_

#include "map/View.hpp"
#include "position/Position.hpp"

#include "utility/defines.hpp"

namespace SimpleNethack {
class ViewManager {
 public:
  /**
   * @brief Destroy the View Manager object
   *
   */
  ~ViewManager();

  /**
   * @brief Get the Instance object
   *
   * @return shared_ptr<ViewManager>
   */
  static shared_ptr<ViewManager> GetInstance();

  /**
   * @brief
   *
   */
  void clear();

  /**
   * @brief Get the View object
   *
   * @param id
   * @return shared_ptr<View>
   */
  shared_ptr<View> GetView(int floor, const Position& pos = Position(2, 2));

 private:
  /**
   * @brief Construct a new View Manager object
   *
   */
  ViewManager();

 private:
  vector<shared_ptr<View>> views_;
  static shared_ptr<ViewManager> instance_;
};
}  // namespace SimpleNethack

#endif