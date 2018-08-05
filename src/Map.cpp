// Map.cpp
#include "Map.hpp"

// default constructor
Map::Map() {
  width_ = ROOM_MAX_WIDTH * 3 + 4;
  height_ = ROOM_MAX_HEIGTH * 3 + 4;
  // create map
  map_ = new char*[height_];
  for (int i = 0; i < height_; i++) {
    map_[i] = new char[width_];
    for (int j = 0; j < width_; j++) {
      map_[i][j] = ' ';
    }
  }
  // create view
  view_ = new bool*[height_];
  for (int i = 0; i < height_; i++) {
    view_[i] = new bool[width_];
    for (int j = 0; j < width_; j++) {
      view_[i][j] = false;
    }
  }
  // create rooms
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Room room(ROOM_MAX_HEIGTH * i + i + 1, ROOM_MAX_WIDTH * j + j + 1);
      room_vector_.push_back(room);
    }
  }
  // set walls
  for (const Room& room : room_vector_) {
    for (int i = room.GetUx(); i <= room.GetDx(); i++) {
      map_[i][room.GetLy()] = WALL;
      map_[i][room.GetRy()] = WALL;
    }
    for (int i = room.GetLy(); i <= room.GetRy(); i++) {
      map_[room.GetUx()][i] = WALL;
      map_[room.GetDx()][i] = WALL;
    }
  }
  // set floor_
  for (const Room& room : room_vector_) {
    for (int i = room.GetUx() + 1; i < room.GetDx(); i++) {
      for (int j = room.GetLy() + 1; j < room.GetRy(); j++) {
        map_[i][j] = FLOOR;
      }
    }
  }
  // set paths
  for (int i = 0; i < 3; i++) {
    SetPath(room_vector_[i * 3].GetDoor()[1],
            room_vector_[i * 3 + 1].GetDoor()[3]);
    SetPath(room_vector_[i * 3 + 1].GetDoor()[1],
            room_vector_[i * 3 + 2].GetDoor()[3]);
    SetPath(room_vector_[i].GetDoor()[2], room_vector_[i + 3].GetDoor()[0]);
    SetPath(room_vector_[i + 3].GetDoor()[2], room_vector_[i + 6].GetDoor()[0]);
  }
  // set stairs
  int t = DOWNSTAIR_NUMBER;
  while (t--) {
    downstair_ = room_vector_[rand(0, 8)].FindSpace();
    map_[downstair_.x][downstair_.y] = DOWNSTAIR;
  }
  // set 4 Potion on map
  int i = ITEM_NUMBER;
  while (i--) {
    while (true) {
      Pos pos = room_vector_[rand(0, 8)].FindSpace();
      Item item(rand(0, 2));  // choose from three items
      if (map_[pos.x][pos.y] == FLOOR) {
        map_[pos.x][pos.y] = item.GetSymbol();
        break;
      }
    }
  }
  // appear weapon by probability 3/9
  if (rand(0, 8) < 3) {
    std::uniform_int_distribution<int> rand_item(3, 4);
    // for (int i = 0; i < 80; i++) {
    while (true) {
      Pos pos = room_vector_[rand(0, 8)].FindSpace();
      Item item(rand(0, 2));  // choose from two weapons
      if (map_[pos.x][pos.y] == FLOOR) {
        map_[pos.x][pos.y] = item.GetSymbol();
        break;
      }
    }
  }
  // other set
  // for some more doors and floor_
  OtherSet();
}

// copy constructor
Map::Map(const Map& other)
    : width_(other.width_),
      height_(other.height_),
      room_vector_(other.room_vector_),
      upstair_(other.upstair_),
      downstair_(other.downstair_) {
  // copy map
  map_ = new char*[height_];
  for (int i = 0; i < height_; i++) {
    map_[i] = new char[width_];
    for (int j = 0; j < width_; j++) {
      map_[i][j] = other.map_[i][j];
    }
  }
  // copy view
  view_ = new bool*[height_];
  for (int i = 0; i < height_; i++) {
    view_[i] = new bool[width_];
    for (int j = 0; j < width_; j++) {
      view_[i][j] = other.view_[i][j];
    }
  }
}

// destructor
Map::~Map() {
  // delete map
  if (map_) {
    for (int i = 0; i < height_; i++) {
      if (map_[i]) {
        delete[] map_[i];
        map_[i] = nullptr;
      }
    }
    delete[] map_;
    map_ = nullptr;
  }
  // delete view
  if (view_) {
    for (int i = 0; i < height_; i++) {
      if (view_[i]) {
        delete[] view_[i];
        view_[i] = nullptr;
      }
    }
    delete[] view_;
    view_ = nullptr;
  }
}

// copy constructor
Map& Map::operator=(const Map& other) {
  width_ = other.width_;
  height_ = other.height_;
  room_vector_ = other.room_vector_;
  upstair_ = other.upstair_;
  downstair_ = other.downstair_;
  // copy map
  map_ = new char*[height_];
  for (int i = 0; i < height_; i++) {
    map_[i] = new char[width_];
    for (int j = 0; j < width_; j++) {
      map_[i][j] = other.map_[i][j];
    }
  }
  // copy view
  view_ = new bool*[height_];
  for (int i = 0; i < height_; i++) {
    view_[i] = new bool[width_];
    for (int j = 0; j < width_; j++) {
      view_[i][j] = other.view_[i][j];
    }
  }
  return *this;
}

// set path between the doors of rooms
void Map::SetPath(const Door& d1, const Door& d2) {
  int x = d1.x;
  int y = d1.y;
  int tx = d2.x;
  int ty = d2.y;
  int dx = x > tx ? -1 : 1;
  int dy = y > ty ? -1 : 1;
  if (map_[tx - dx][ty] != ' ')
    ty -= dy;
  else
    tx -= dx;
  map_[tx][ty] = PATH;
  std::random_device e;
  while (x != tx || y != ty) {
    if ((x + dx == tx && y == ty) || (x == tx && y + dy == ty)) break;
    if (x == tx || map_[x + dx][y] != ' ')
      y += dy;
    else {
      if (y == ty || map_[x][y + dy] != ' ')
        x += dx;
      else {
        std::uniform_int_distribution<int> rand(0, 1);
        if (rand(e))
          x += dx;
        else
          y += dy;
      }
    }
    map_[x][y] = PATH;
    if ((x + dx == tx && y == ty) || (x == tx && y + dy == ty)) break;
  }
  std::uniform_int_distribution<int> rand(0, 5);
  map_[d1.x][d1.y] = rand(e) < 1 ? OPEN_DOOR : CLOSED_DOOR;
  map_[d2.x][d2.y] = rand(e) < 1 ? OPEN_DOOR : CLOSED_DOOR;
}

// for some more door and floor_
void Map::OtherSet() {
  Door door = room_vector_[5].GetDoor()[1];
  map_[door.x][door.y] = CLOSED_DOOR;
  map_[door.x][door.y + 1] = FLOOR;
  door = room_vector_[6].GetDoor()[2];
  map_[door.x][door.y] = CLOSED_DOOR;
  map_[door.x + 1][door.y] = FLOOR;
}

// get width of the map
int Map::GetWidth() const {
  return width_;
}

// get height of the map
int Map::GetHeight() const {
  return height_;
}

// get the char of the map at the position
char Map::GetMapChar(Pos pos) const {
  return map_[pos.x][pos.y];
}

// get whether the map of the position is viewed
bool Map::GetView(Pos pos) const {
  return view_[pos.x][pos.y];
}

//// get upstair
// Pos  Map::GetUpstair() const {
//	return upstair_;
//}
//
// get downstair
Pos Map::GetDownstair() const {
  return downstair_;
}

// print the whole map
void Map::PrintMap() {
  Pos::SetCursor(0, 0);
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      cout << map_[i][j];
    }
    cout << endl;
  }
}

// to change the map of the position
void Map::ChangeMap(Pos pos, char c) {
  map_[pos.x][pos.y] = c;
  Pos::SetCursor(pos.x, pos.y);
  cout << c;
}

// to change the map of the position
void Map::ChangeView(Pos pos) {
  view_[pos.x][pos.y] = true;
}

// determine whether can go to the position
bool Map::CanMove(Pos pos) const {
  if (pos.x >= height_ || pos.x < 0 || pos.y >= width_ || pos.y < 0)
    return false;
  if (map_[pos.x][pos.y] == WALL || map_[pos.x][pos.y] == CLOSED_DOOR ||
      map_[pos.x][pos.y] == ' ')
    return false;  // bug
  else
    return true;
}

// to find a position that is floor_
Pos Map::FindSpace() const {
  std::random_device e;
  std::uniform_int_distribution<int> rroom(0, 8);
  return room_vector_[rroom(e)].FindSpace();
}

// compute the distance from position A to position B
int Map::ComputeDistance(Pos startPos, Pos endPos) const {
  if (startPos == endPos) return 0;
  bool** used = new bool*[height_];
  for (int i = 0; i < height_; i++) {
    used[i] = new bool[width_];
    for (int j = 0; j < width_; j++) {
      used[i][j] = false;
    }
  }
  Queue que;
  Pos pos = startPos;
  que.push(pos);
  used[pos.x][pos.y] = true;
  Pos tail = que.front();
  int step = 0;
  while (!que.empty()) {
    if (step > 80) return INF;
    Direction d(0);
    int i = 8;
    while (i--) {
      pos = que.front() + --d;
      if (pos == endPos) return step;
      if (CanMove(pos) && !used[pos.x][pos.y]) {
        que.push(pos);
        used[pos.x][pos.y] = true;
      }
    }
    if (tail == que.front()) {
      step++;
      tail = que.back();
    }
    que.pop();
  }
  return INF;
}

// set stair
void Map::SetUpStair(Pos pos) {
  upstair_ = pos;
  map_[pos.x][pos.y] = UPSTAIR;
}

void Map::SetNecklace() {
  Pos pos = room_vector_[5].GetDoor()[1] + Direction(1);
  map_[pos.x][pos.y] = '&';
}
