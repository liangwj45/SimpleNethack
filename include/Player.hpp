// Player.hpp
#ifndef _HUMAN_
#define _HUMAN_
#include <string>
#include "Creature.hpp"
#include "Item.hpp"
using std::string;

class Player : public Creature {
public:
	Player();
	Player(const Pos& pos);
	void Recover();
	// hp_ + 15, mp_ - 3
	bool Heal();
	// level_ up if exp_ more than 20 * level_
	bool Grow(int ep);
	int GetLevel();
	int GetExp();
	int GetMp();
	int GetMaxMp();
	int GetCount();
	void ChangeMp(int t);
	bool PickUp(char c);
	Direction GetDirection() const;
	void SetDirection(Direction dir);
public:
	bool UseItem(int i);
	bool IsWeaponed();
	Item GetWeapon();
	vector<std::pair<Item, int>> GetBag();
	int BagSize();
private:
	int level_;
	int exp_;
	int mp_;
	int max_mp_;
	bool weaponed_;
	Item weapon_;
	Direction direction_;
	vector<std::pair<Item,int>> bag_;
};

#endif // !_HUMAN_
