#include "map/MapManager.hpp"

namespace SimpleNethack {

shared_ptr<MapManager> MapManager::instance_ = nullptr;

shared_ptr<MapManager> MapManager::GetInstance() {
  if (!instance_) {
    instance_.reset(new MapManager());
  }
  return instance_;
}

shared_ptr<Map> MapManager::GetMap(int floor, const Position& pos) {
  if (maps_.size() <= floor) {
    maps_.push_back(make_shared<Map>(pos));
  }
  return maps_[floor];
}

MapManager::~MapManager() {}

MapManager::MapManager() {}

}  // namespace SimpleNethack