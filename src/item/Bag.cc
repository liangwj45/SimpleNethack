#include "item/Bag.hpp"

namespace SimpleNethack {
bool Bag::Add(const Item& item) {
  // TO:: add weight
  for (auto& each : item_list_) {
    if (each.first == item) {
      ++each.second;
      return true;
    }
  }
  item_list_.push_back(make_pair(item, 1));
  return true;
}

bool Bag::Use(int id) {
  --item_list_[id].second;
  if (item_list_[id].second == 0) {
    auto index = item_list_.begin();
    while (id--) {
      ++index;
    }
    item_list_.erase(index);
  }
  return true;
}
}  // namespace SimpleNethack