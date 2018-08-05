#include "creature/MonsterManager.hpp"

namespace SimpleNethack {

shared_ptr<MonsterManager> MonsterManager::instance_ = nullptr;

shared_ptr<MonsterManager> MonsterManager::GetInstance() {
  if (!instance_) {
    instance_.reset(new MonsterManager());
  }
  return instance_;
}

void MonsterManager::clear() { monsters_.clear(); }

MonsterManager::MonsterManager() {}

MonsterManager::~MonsterManager() {}

shared_ptr<list<Monster>> MonsterManager::GetMonsters(int floor) {
  if (monsters_.size() <= floor) {
    monsters_.push_back(make_shared<list<Monster>>());
  }
  return monsters_[floor];
}

}  // namespace SimpleNethack