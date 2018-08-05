#include "utility/Utility.hpp"

namespace SimpleNethack {
void SetColor(int color) {
  static HANDLE honsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(honsole, color);
}

void SetCursor(int x, int y) {
  static HANDLE honsole = GetStdHandle(STD_OUTPUT_HANDLE);
  static COORD coord;
  coord.X = y;
  coord.Y = x;
  SetConsoleCursorPosition(honsole, coord);
}

void SetCursor(const Position pos) { SetCursor(pos.x, pos.y); }

std::string tostring(const int& t) { return std::to_string(t); }

int rand(int s, int t) {
  static unsigned int let_more_random = 16303050;
  srand((unsigned int)time(nullptr) * let_more_random++);
  return std::rand() % (t - s + 1) + s;
}

int ComputeXY(const Position& lhs, const Position& rhs) {
  return abs(lhs.x - rhs.x) + abs(lhs.y - rhs.y);
}
}  // namespace SimpleNethack