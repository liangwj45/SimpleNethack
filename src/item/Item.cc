#include "item/Item.hpp"

namespace SimpleNethack {

vector<char> Item::symbol_({'R', 'B', 'W', 'I', '$', '&'});
vector<int> Item::atk_({0, 0, 0, 2, 5, 0});
vector<string> Item::name_({"Healing Potion", "Mana Potion", "Water",
                            "Warrior Sword", "Magic Rod", "Queen's Necklace"});
vector<string> Item::type_({"Potion", "Potion", "Potion", "Weapon", "Weapon",
                            "Artifact"});

Item::Item(int i) : id_(i % 6) {}

Item::Item(char c) {
  for (int i = 0; i < 6; ++i) {
    if (c == symbol_[i]) {
      id_ = i;
      return;
    }
  }
  id_ = 2;
}

bool Item::operator==(const Item& other) const { return id_ == other.id_; }

int Item::GetNum() const { return id_; }

char Item::GetSymbol() const { return symbol_[id_]; }

int Item::GetDatk() const { return atk_[id_]; }

string Item::GetName() const { return name_[id_]; }

string Item::GetType() const { return type_[id_]; }

bool Item::IsItem(char c) {
  for (char ch : symbol_) {
    if (ch == c) {
      return true;
    }
  }
  return false;
}

}  // namespace SimpleNethack