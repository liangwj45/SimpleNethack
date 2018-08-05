#include "position/Position.hpp"

namespace SimpleNethack {

Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position& pos) const {
  return (x == pos.x && y == pos.y);
}

bool Position::operator!=(const Position& pos) const {
  return (x != pos.x && y != pos.y);
}

Position Position::operator+(const Direction& dir) const {
  return Position(x + dir.GetDx(), y + dir.GetDy());
}

Position& Position::operator+=(const Direction& dir) {
  x += dir.GetDx();
  y += dir.GetDy();
  return *this;
}
}  // namespace SimpleNethack