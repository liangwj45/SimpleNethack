// Player.cpp
#include "Player.hpp"

Player::Player() :Creature() {
	atk_ = 8;
	floor_ = 0;
	level_ = 1;
	exp_ = 0;
	hp_ = 50;
	max_hp_ = 50;
	mp_ = 5;
	max_mp_ = 5;
	direction_ = Direction(0);
	symbol_ = PLAYER;
}

Player::Player(const Pos& pos) :Creature(pos) {
	atk_ = 8;
	floor_ = 0;
	level_ = 1;
	exp_ = 0;
	hp_ = 50;
	max_hp_ = 50;
	mp_ = 5;
	max_mp_ = 5;
	direction_ = Direction(0);
	symbol_ = PLAYER;
}

// hp_ + 1 every 10 round, mp_ + 1 every 20 round
void Player::Recover() {
	recover_count_++;
	if (recover_count_ % 10 == 0) {
		if (hp_ < max_hp_) hp_++;
	}
	if (recover_count_ % 20 == 0) {
		if (mp_ < max_mp_) mp_++;
		recover_count_ = 0;
	}
}

// hp_ + 15, mp_ - 3
bool Player::Heal() {
	if (hp_ >= max_hp_) return false;
	if (mp_ < 3) return false;
	mp_ -= 3;
	hp_ += 15;
	if (hp_ > max_hp_) hp_ = max_hp_;
	return true;
}

// level_ up if exp_ more than 20 * level_
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

int Player::GetLevel() {
	return level_;
}

int Player::GetExp() {
	return exp_;
}

int Player::GetMp() {
	return mp_;
}

int Player::GetMaxMp() {
	return max_mp_;
}

int Player::GetCount() {
	return recover_count_;
}

void Player::ChangeMp(int t) {
	mp_ += t;
}

bool Player::PickUp(char c) {
	Item item(c);
	for (auto& each : bag_) {
		if (each.first == item) {
			++each.second;
			return true;
		}
	}
	bag_.push_back(std::make_pair(item, 1));
	return true;
}

Direction Player::GetDirection() const {
	return direction_;
}

void Player::SetDirection(Direction dir) {
	direction_ = dir;
}

bool Player::UseItem(int i) {
	Item item = bag_[i].first;
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
		if (weaponed_) atk_ -= weapon_.GetDatk();
		break;
	default:
		return false;
	}
	int j = i;
	auto index = bag_.begin();
	while (j--) index++;
	if (!--bag_[i].second) bag_.erase(index);
	// weapon
	if (i_ == 3 || i_ == 4) {
		if (weaponed_) PickUp(weapon_.GetSymbol());
		weapon_ = item;
		weaponed_ = true;
	}
	return true;
}

bool Player::IsWeaponed() {
	return weaponed_;
}

Item Player::GetWeapon() {
	return weapon_;
}

vector<std::pair<Item, int>> Player::GetBag() {
	return bag_;
}

int Player::BagSize() {
	return bag_.size();
}