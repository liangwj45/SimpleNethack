#include "map/ViewManager.hpp"

namespace SimpleNethack {

shared_ptr<ViewManager> ViewManager::instance_ = nullptr;

shared_ptr<ViewManager> ViewManager::GetInstance() {
  if (!instance_) {
    instance_.reset(new ViewManager());
  }
  return instance_;
}

void ViewManager::clear() { views_.clear(); }

shared_ptr<View> ViewManager::GetView(int floor, const Position& pos) {
  if (views_.size() <= floor) {
    views_.push_back(make_shared<View>(pos));
  }
  return views_[floor];
}

ViewManager::~ViewManager() {}

ViewManager::ViewManager() {}

}  // namespace SimpleNethack