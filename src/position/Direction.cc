#include "position/Direction.hpp"

namespace SimpleNethack {
int Direction::dir_[8][2] = {{-1, 0}, {0, 1}, {1, 0},  {0, -1},
                             {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

Direction::Direction(int t) : i_(t % 8) {}

int Direction::GetDx() const { return dir_[i_][0]; }

int Direction::GetDy() const { return dir_[i_][1]; }

Direction& Direction::operator++() {
  i_ = (i_ + 1) % 8;
  return *this;
}

Direction& Direction::operator--() {
  i_ = (i_ + 7) % 8;
  return *this;
}

Direction& Direction::operator+=(int t) {
  i_ = (i_ + t) % 8;
  return *this;
}

Direction& Direction::operator-=(int t) {
  i_ = (i_ - t % 8 + 8) % 8;
  return *this;
}
}  // namespace SimpleNethack