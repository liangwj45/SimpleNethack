#include "map/Map.hpp"
namespace SimpleNethack {

Map::Map(const Position& pos) {
  CreateBasicMap();
  int upi = CreateRooms(pos);
  SetWall();
  SetFloor();
  SetPaths();
  SetDownstair(pos, upi);
  SetUpstair(pos);
  OtherSet();
}

void Map::CreateBasicMap() {
  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      map_[i][j] = ' ';
    }
  }
}

int Map::CreateRooms(const Position& pos) {
  int upi = 0;
  int x = pos.x;
  int y = pos.y;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int ux = ROOM_HEIGHT_MAX * i + i + 1;
      int dx = ux + ROOM_HEIGHT_MAX;
      int ly = ROOM_WIDTH_MAX * j + j + 1;
      int ry = ly + ROOM_WIDTH_MAX;
      Room room(ux, ly);
      if (ux < x && dx > x && ly < y && ry > y) {
        upi = i * 3 + j;
        while (!room.InRoom(pos)) {
          room = std::move(Room(ux, ly));
        }
      }
      room_vector_.push_back(std::move(room));
    }
  }
  std::for_each(room_vector_.begin(), room_vector_.end(),
                [](Room& each) { each.SetDoor(); });
  return upi;
}

void Map::SetWall() {
  for (const Room& room : room_vector_) {
    for (int i = room.ux_; i <= room.dx_; i++) {
      map_[i][room.ly_] = WALL;
      map_[i][room.ry_] = WALL;
    }
    for (int i = room.ly_; i <= room.ry_; i++) {
      map_[room.ux_][i] = WALL;
      map_[room.dx_][i] = WALL;
    }
  }
}

void Map::SetFloor() {
  for (const Room& room : room_vector_) {
    for (int i = room.ux_ + 1; i < room.dx_; i++) {
      for (int j = room.ly_ + 1; j < room.ry_; j++) {
        map_[i][j] = FLOOR;
      }
    }
  }
}

void Map::SetPaths() {
  for (int i = 0; i < 3; i++) {
    SetPath(room_vector_[i * 3][1], room_vector_[i * 3 + 1][3]);
    SetPath(room_vector_[i * 3 + 1][1], room_vector_[i * 3 + 2][3]);
    SetPath(room_vector_[i][2], room_vector_[i + 3][0]);
    SetPath(room_vector_[i + 3][2], room_vector_[i + 6][0]);
  }
}

void Map::SetDownstair(const Position& pos, int upi) {
  int downi = 0;
  while (abs(downi - upi) < 2 || abs(downi - upi) == 3) downi = rand(0, 8);
  Position downp = room_vector_[downi].FindSpace();
  ChangeMap(pos, DOWNSTAIR);
}

void Map::SetUpstair(const Position& pos) {
  upstair_ = pos;
  ChangeMap(upstair_, UPSTAIR);
}

void Map::OtherSet() {
  Door door = room_vector_[5][1];
  map_[door.x][door.y] = CLOSED_DOOR;
  map_[door.x][door.y + 1] = FLOOR;
  door = room_vector_[6][2];
  map_[door.x][door.y] = CLOSED_DOOR;
  map_[door.x + 1][door.y] = FLOOR;
}

Map::Map(const Map& other)
    : upstair_(other.upstair_), downstair_(other.downstair_) {
  for (int i = 0; i < MAX_MAP_HEIGHT; ++i) {
    for (int j = 0; j < MAX_MAP_WIDTH; ++j) {
      this->map_[i][j] = other.map_[i][j];
    }
  }
  room_vector_ = other.room_vector_;
}

void Map::PrintMap() const {
  SetCursor(0, 0);
  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      std::cout << map_[i][j];
    }
    std::cout << std::endl;
  }
}

char Map::GetMapChar(const Position& pos) const { return map_[pos.x][pos.y]; }

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
  while (x != tx || y != ty) {
    if ((x + dx == tx && y == ty) || (x == tx && y + dy == ty)) break;
    if (x == tx || map_[x + dx][y] != ' ')
      y += dy;
    else {
      if (y == ty || map_[x][y + dy] != ' ')
        x += dx;
      else {
        if (rand(0, 1))
          x += dx;
        else
          y += dy;
      }
    }
    map_[x][y] = PATH;
    if ((x + dx == tx && y == ty) || (x == tx && y + dy == ty)) break;
  }
  map_[d1.x][d1.y] = rand(0, 5) < 1 ? OPEN_DOOR : CLOSED_DOOR;
  map_[d2.x][d2.y] = rand(0, 5) < 1 ? OPEN_DOOR : CLOSED_DOOR;
}

int Map::ComputeDistance(const Position& lhs, const Position& rhs) const {
  if (lhs == rhs) return 0;
  bool used[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]{false};
  std::queue<Position> que;
  Position pos = lhs;
  que.push(pos);
  used[pos.x][pos.y] = true;
  Position tail = que.front();
  int step = 0;
  while (!que.empty()) {
    if (step > 80) return INF;
    Direction d(0);
    for (int i = 0; i < 8; ++i) {
      pos = que.front() + --d;
      if (pos == rhs) return step + 1;
      if (map_[pos.x][pos.y] != WALL && map_[pos.x][pos.y] != CLOSED_DOOR &&
          !used[pos.x][pos.y]) {
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

Position Map::FindSpace() const { return room_vector_[rand(0, 8)].FindSpace(); }

void Map::ChangeMap(const Position& pos, char c) { map_[pos.x][pos.y] = c; }

void Map::SetNecklace() { ChangeMap(room_vector_[5][1] + Direction(1), '&'); }

Map::Room::Room(int ux, int ly) {
  int width = rand(ROOM_WIDTH_MIN, ROOM_WIDTH_MAX);
  int height = rand(ROOM_HEIGHT_MIN, ROOM_HEIGHT_MAX);
  ux_ = rand(ux, ux + ROOM_HEIGHT_MAX - height);
  ly_ = rand(ly, ly + ROOM_WIDTH_MAX - width);
  ry_ = ly_ + width - 1;
  dx_ = ux_ + height - 1;
}

void Map::Room::SetDoor() {
  int x = rand(ux_ + 1, dx_ - 1);
  int y = rand(ly_ + 1, ry_ - 1);
  for (int i = 0; i < 4; i++) {
    switch (i) {
      case 0:
        door_vector_.push_back(Door(ux_, y));
        break;
      case 1:
        door_vector_.push_back(Door(x, ry_));
        break;
      case 2:
        door_vector_.push_back(Door(dx_, y));
        break;
      case 3:
        door_vector_.push_back(Door(x, ly_));
        break;
      default:
        break;
    }
  }
}

Position Map::Room::FindSpace() const {
  int x = rand(ux_ + 1, dx_ - 1);
  int y = rand(ly_ + 1, ry_ - 1);
  return Position(x, y);
}

bool Map::Room::InRoom(const Position& pos) {
  int x = pos.x;
  int y = pos.y;
  return ux_ < x && dx_ > x && ly_ < y && ry_ > y;
}

Map::Door& Map::Room::operator[](int id) { return door_vector_[id]; }

Map::Door::Door(int x, int y) : Position(x, y) {}

}  // namespace SimpleNethack