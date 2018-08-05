#include "creature/Player.hpp"

namespace SimpleNethack {

shared_ptr<Player> Player::instance_ = nullptr;

shared_ptr<Player> Player::GetInstance(const Position& pos) {
  if (!instance_) {
    instance_.reset(new Player(pos));
  }
  return instance_;
}

void Player::Destroy() { instance_ = nullptr; }

Player::Player(const Position& pos, int hp, int atk) : Creature(pos, hp, atk) {
  symbol_ = PLAYER;
  bag_.reset(new Bag);
}

Player::~Player() {}

void Player::Recover() {
  recover_count_++;
  if (recover_count_ % 10 == 0 && hp_ < max_hp_) hp_++;
  if (recover_count_ % 20 == 0 && mp_ < max_mp_) mp_++;
  if (recover_count_ == 20) recover_count_ = 0;
}

void Player::Heal() {
  mp_ -= 3;
  hp_ += 15;
  if (hp_ > max_hp_) hp_ = max_hp_;
}

bool Player::Grow(int ep) {
  exp_ += ep;
  if (exp_ >= 20 * level_) {
    exp_ -= 20 * level_;
    level_++;
    hp_ += 5;
    max_hp_ += 5;
    mp_ += 1;
    max_mp_ += 1;
    atk_ += 2;
    return true;
  }
  return false;
}

bool Player::PickUp(const Item& item) { return bag_->Add(item); }

bool Player::UseItem(int id) {
  Item item = bag_->item_list_[id].first;
  int i_ = item.GetNum();
  switch (i_) {
    case 0:
      if (hp_ >= max_hp_) return false;
      hp_ += 10;
      if (hp_ > max_hp_) hp_ = max_hp_;
      break;
    case 1:
      if (mp_ >= max_mp_) return false;
      mp_ += 3;
      if (mp_ > max_mp_) mp_ = max_mp_;
      break;
    case 2:
      break;
    case 3:
    case 4:
      atk_ += item.GetDatk();
      if (weaponed_) atk_ -= weapon_->GetDatk();
      break;
    default:
      return false;
  }
  int j = id;
  auto index = bag_->item_list_.begin();
  while (j--) index++;
  if (!--bag_->item_list_[id].second) bag_->item_list_.erase(index);
  // weapon
  if (i_ == 3 || i_ == 4) {
    if (weaponed_) PickUp(weapon_->GetSymbol());
    weapon_.reset(&item);
    weaponed_ = true;
  }
  return true;
}

bool Player::IsWeaponed() const { return weaponed_; }

int Player::GetLevel() const { return level_; }

int Player::GetExp() const { return exp_; }

int Player::GetMp() const { return mp_; }

int Player::GetMaxMp() const { return max_mp_; }

shared_ptr<Item> Player::GetWeapon() const { return weapon_; }

shared_ptr<Bag> Player::GetBag() const { return bag_; }
}  // namespace SimpleNethack