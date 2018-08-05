#ifndef _BAG_
#define _BAG_

#include "item/Item.hpp"

#include "utility/defines.hpp"

namespace SimpleNethack {
struct Bag {
  /**
   * @brief
   *
   * @param item
   * @return true
   * @return false
   */
  bool Add(const Item& item);

  /**
   * @brief
   *
   * @param id
   * @return true
   * @return false
   */
  bool Use(int id);

  vector<pair<Item, int>> item_list_;

  // TO:: add weight
  // int max_weight_ = 50;
};

}  // namespace SimpleNethack

#endif