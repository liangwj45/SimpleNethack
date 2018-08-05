#include "map/View.hpp"
namespace SimpleNethack {

View::View(const Position& pos) {
  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      view_[i][j] = false;
    }
  }
}

View::View(const View& other) {
  for (int i = 0; i < MAX_MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAX_MAP_WIDTH; ++j) {
      this->view_[i][j] = other.view_[i][j];
    }
  }
}

bool View::GetView(const Position& pos) const { return view_[pos.x][pos.y]; }

void View::UpdateView(const Position& pos) { view_[pos.x][pos.y] = true; }

bool& View::operator[](const Position& pos) { return view_[pos.x][pos.y]; }

bool View::operator()(const Position& pos) { return view_[pos.x][pos.y]; }

}  // namespace SimpleNethack