// Item.hpp
#ifndef _ITEM_
#define	_ITEM_
#include <string>
using std::string;

class Item {
public:
	Item() {
		i_ = 2;
	}
	Item(int i) {
		i_ = i % 6;
	}
	Item(char c) {
		int i = 5;
		while (i--) {
			if (c == symbol_[i]) {
				i_ = i;
				return;
			}
		}
		i_ = 2;
	}
	Item(const Item& other) = default;
	Item operator=(const Item& other) {
		i_ = other.i_;
		return *this;
	}
	int GetNum() {
		return i_;
	}
	int GetDatk() {
		return atk_[i_];
	}
	string GetName() {
		return name_[i_];
	}
	char GetSymbol() {
		return symbol_[i_];
	}
	/*int GetWeight() {
		return weight_[i_];
	}*/
	bool operator==(const Item& other) {
		return i_ == other.i_;
	}
private:
	int i_;
	char symbol_[6] = { 'R', 'B', 'W', 'I', '$', '&' };
	//int weight_[6] = { 1,1,1,1,1,0 };
	int atk_[6] = { 0,0,0,2,5,0 };
	string name_[6] = { "Healing Potion", "Mana Potion", "Water", "Warrior Sword", "Magic Rod", "Queen's Necklace" };
};

#endif // !_ITEM_