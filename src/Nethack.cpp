// Nethack.cpp
#include "Nethack.hpp"

Nethack::Nethack() {
  InitialGame();
}

void Nethack::InitialGame() {
  // create map
  map_vector_.clear();
  Map map;
  map_vector_.push_back(map);

  // create player
  Pos pos = map.FindSpace();
  player_ = std::shared_ptr<Player>(new Player(pos));

  // create monster
  monsters_.clear();
  list<Monster> molist;
  monsters_.push_back(molist);
  for (int i = 0; i < MONSTER_INITIAL_NUMBER; i++) {
    CreateMonster();
  }

  // set Goldenfinger
  see_monster_ = false;
}

void Nethack::PrintMap() {
  Map& map = map_vector_[player_->GetFloor()];
  Pos::SetCursor(0, 0);
  for (int i = 0; i < map.GetHeight(); i++) {
    for (int j = 0; j < map.GetWidth(); j++) {
      Pos::SetCursor(i, j);
      Pos pos(i, j);
      if (InMap(pos)) {
        cout << (map.GetView(pos) ? map.GetMapChar(pos) : ' ');
      }
    }
  }
  // map_vector_[player_->GetFloor()].PrintMap();
}

void Nethack::PrintMonster() {
  Pos mpos;
  for (Monster& monster : monsters_[player_->GetFloor()]) {
    mpos = monster.GetPos();
    if (CanSee(mpos)) {
      UpdateMap(mpos, MONSTER_COLOR, monster.GetSymbol());
    }
  }
}

void Nethack::Vision() {
  Pos pos = player_->GetPos();

  // print vision
  Map& map = map_vector_[player_->GetFloor()];
  for (int i = -VISION_RANGE; i <= VISION_RANGE; i++) {
    for (int j = -VISION_RANGE; j <= VISION_RANGE; j++) {
      Pos p(pos.x + i, pos.y + j);
      if (CanSee(p)) {
        map.ChangeView(p);
        UpdateMap(p, LIGHT_COLOR, GetMapChar(p));
      } else if (InMap(p)) {
        char c =
            map_vector_[player_->GetFloor()].GetView(p) ? GetMapChar(p) : ' ';
        UpdateMap(p, 7, c);
      }
    }
  }

  // print center
  UpdateMap(pos, PLAYER_COLOR, PLAYER);

  // hide vision outof vision_range
  int x = pos.x - VISION_RANGE - 1;
  int y = pos.y - VISION_RANGE - 1;
  for (int i = x; i < x + VISION_RANGE * 2 + 2; i++) {
    for (int j = 0; j < 2; j++) {
      Pos p(i, y + (VISION_RANGE * 2 + 2) * j);
      if (InMap(p)) {
        char c =
            map_vector_[player_->GetFloor()].GetView(p) ? GetMapChar(p) : ' ';
        UpdateMap(p, 7, c);
      }
    }
  }
  for (int i = y; i < y + VISION_RANGE * 2 + 2; i++) {
    for (int j = 0; j < 2; j++) {
      Pos p(x + (VISION_RANGE * 2 + 2) * j, i);
      if (InMap(p)) {
        char c =
            map_vector_[player_->GetFloor()].GetView(p) ? GetMapChar(p) : ' ';
        UpdateMap(p, 7, c);
      }
    }
  }
}

void Nethack::ChangeMap(Pos pos, char c) {
  map_vector_[player_->GetFloor()].ChangeMap(pos, c);
}

int Nethack::GetMonsterCount() {
  return monsters_[player_->GetFloor()].size();
}

Monster& Nethack::GetMonster(Pos pos) {
  for (Monster& each : monsters_[player_->GetFloor()]) {
    if (pos == each.GetPos()) {
      return each;
    }
  }
}

std::shared_ptr<Player> Nethack::GetPlayer() {
  UpdateMap(player_->GetPos(), LIGHT_COLOR, PLAYER);
  return player_;
}

// player

bool Nethack::move(Direction dir) {
  player_->SetDirection(dir);
  Pos pos = player_->GetPos();
  if (CanMove(pos + dir)) {
    player_->Move(dir);
    return true;
  } else
    return false;
}

bool Nethack::Attack() {
  Direction dir = player_->GetDirection();
  Pos pos = player_->GetPos();
  for (int i = 0; i < 1; i++) {
    pos += dir;
    if (IsMonster(pos)) {
      Monster& monster = GetMonster(pos);
      monster.Hurt(player_->GetAtk());
      UpdateMap(monster.GetPos(), LIGHT_COLOR, monster.GetSymbol());
      Sleep(50);
      UpdateMap(monster.GetPos(), MONSTER_COLOR, monster.GetSymbol());
      return true;
    }
  }
  return false;
}

bool Nethack::Heal() {
  return player_->Heal();
}

bool Nethack::OpenDoor() {
  Pos ppos = player_->GetPos();
  int floor = player_->GetFloor();
  Direction dir = player_->GetDirection();
  Pos door_pos = ppos + dir;
  if (InMap(door_pos) && GetMapChar(door_pos) == CLOSED_DOOR) {
    map_vector_[player_->GetFloor()].ChangeMap(door_pos, OPEN_DOOR);
    return true;
  }
  return false;
}

bool Nethack::ChangeStair() {
  char c = GetMapChar(player_->GetPos());
  if (c == UPSTAIR) {
    player_->ChangeFloor(-1);
    CleanMap();
    PrintMap();
    return true;
  }
  if (c == DOWNSTAIR) {
    CleanMap();
    player_->ChangeFloor(1);
    if (player_->GetFloor() == map_vector_.size()) {
      Pos ppos = player_->GetPos();
      Map map;
      bool bottom = player_->GetFloor() == 9 ? true : false;
      if (bottom) map.SetNecklace();
      while (map.GetMapChar(ppos) != FLOOR ||
             Pos::ComputeXY(ppos, map.GetDownstair()) < 30) {
        map = Map();
        if (bottom) map.SetNecklace();
      }
      map.SetUpStair(ppos);
      map_vector_.push_back(map);
      list<Monster> molist;
      monsters_.push_back(molist);
      for (int i = 0; i < MONSTER_INITIAL_NUMBER + player_->GetFloor(); i++) {
        CreateMonster();
      }
    } else {
      PrintMap();
    }
    return true;
  }
  return false;
}

void Nethack::Goldenfinger() {
  see_monster_ = !see_monster_;
  if (!see_monster_) HideMonster();
}

// monster

void Nethack::MonsterAction() {
  // action of monsters on other floors
  for (int i = 0; i < monsters_.size(); i++) {
    if (i == player_->GetFloor()) continue;
    for (Monster& each : monsters_[i]) {
      Pos mpos = each.GetPos();
      Direction dir = RandomDirection(
          mpos, [&](const Pos p) -> bool { return CanMove(p, i); });
      if (CanMove(mpos + dir, i)) each.Move(dir);
    }
  }

  // action of monsters on player's floor
  bool attacked = false;
  for (Monster& each : monsters_[player_->GetFloor()]) {
    // monsters' action
    each.Recover();
    Pos mpos = each.GetPos();
    if (CanAttackPlayer(mpos)) {
      MonsterAttack(each);
      attacked = true;
      if (player_->GetHp() < 0) {
        return;
      }
    } else
      MonsterMove(each);
  }

  // print player's state
  /*if (attacked) {
          Pos ppos = player_->GetPos();
          UpdateMap(ppos, 12, PLAYER);
          Sleep(50);
          UpdateMap(ppos, PLAYER_COLOR, PLAYER);
  }*/
}

void Nethack::CreateMonster() {
  int floor = player_->GetFloor();
  Pos ppos = player_->GetPos();
  Pos mpos = map_vector_[floor].FindSpace();
  while (mpos == ppos) {
    mpos = map_vector_[floor].FindSpace();
  }
  Monster monster(mpos, floor, 3 + floor / 3, 16 + floor);
  monsters_[floor].push_back(monster);
}

void Nethack::MonsterAttack(Monster& monster) {
  player_->Hurt(monster.GetAtk());
  UpdateMap(monster.GetPos(), MONSTER_COLOR, monster.GetSymbol());
  Pos ppos = player_->GetPos();
  UpdateMap(ppos, 12, PLAYER);
  Sleep(50);
  UpdateMap(ppos, PLAYER_COLOR, PLAYER);
}

void Nethack::MonsterMove(Monster& monster) {
  Pos mpos = monster.GetPos();
  Direction dir;
  if (Pos::ComputeXY(player_->GetPos(), mpos) <= 20)
    dir = FindPath(mpos);
  else
    dir =
        RandomDirection(mpos, [&](const Pos p) -> bool { return CanMove(p); });
  if (CanMove(mpos + dir)) {
    char c =
        map_vector_[player_->GetFloor()].GetView(mpos) ? GetMapChar(mpos) : ' ';
    UpdateMap(mpos, CanSee(mpos) ? LIGHT_COLOR : 7, c);
    monster.Move(dir);
    mpos += dir;
    if (CanSee(mpos) || see_monster_) {
      UpdateMap(mpos, MONSTER_COLOR, monster.GetSymbol());
    }
  }
}

Direction Nethack::FindPath(Pos mpos) {
  Direction mindir;
  Direction d(0);
  Pos ppos = player_->GetPos();
  Pos pos;
  int min_i = 0;
  int min_xy = INF;
  int min_dis = INF;
  int i = 8;
  while (i--) {
    pos = mpos + --d;
    if (CanMove(pos)) {
      int dis = map_vector_[player_->GetFloor()].ComputeDistance(pos, ppos);
      int xy = Pos::ComputeXY(pos, ppos);
      if (dis < min_dis || (dis == min_dis && xy <= min_xy)) {
        min_dis = dis;
        min_xy = xy;
        min_i = i;
      }
    }
  }
  if (min_dis < INF) return Direction(min_i);
  return RandomDirection(mpos, [&](const Pos p) -> bool { return CanMove(p); });
}

Direction Nethack::RandomDirection(Pos pos,
                                   std::function<bool(const Pos pos)> filter) {
  std::random_device e;
  std::uniform_int_distribution<int> rdir(0, 7);
  int i = rdir(e), t = 8;
  Direction d(i);
  while (t-- && !filter(pos + ++d))
    ;
  return d;
}

bool Nethack::CanAttackPlayer(Pos pos) {
  Pos p = player_->GetPos();
  return (abs(pos.x - p.x) <= 1 && abs(pos.y - p.y) <= 1);
}

void Nethack::DeleteMonster(Pos mpos) {
  for (auto it = monsters_[player_->GetFloor()].begin();
       it != monsters_[player_->GetFloor()].end();) {
    if (it->GetPos() == mpos) {
      it = monsters_[player_->GetFloor()].erase(it);
    } else {
      it++;
    }
  }
  Map& map = map_vector_[player_->GetFloor()];
  char c = map.GetView(mpos) ? map.GetMapChar(mpos) : ' ';
  UpdateMap(mpos, LIGHT_COLOR, c);
}

// Map

void Nethack::HideMonster() {
  list<Monster> mlist = monsters_[player_->GetFloor()];
  Map& map = map_vector_[player_->GetFloor()];
  for (Monster& each : mlist) {
    Pos mpos = each.GetPos();
    char c = map.GetView(mpos) ? map.GetMapChar(mpos) : ' ';
    UpdateMap(mpos, 7, c);
  }
}

char Nethack::GetMapChar(Pos pos) {
  return map_vector_[player_->GetFloor()].GetMapChar(pos);
}

void Nethack::UpdateMap(Pos pos, int color, char c) {
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, color);
  Pos::SetCursor(pos);
  cout << c;
  SetConsoleTextAttribute(handle, 7);
}

void Nethack::CleanMap() {
  Pos::SetCursor(0, 0);
  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      cout << ' ';
    }
    cout << endl;
  }
}

bool Nethack::CanSee(Pos pos) {
  if (!InMap(pos)) return false;
  Pos ppos = player_->GetPos();
  Direction arrd[4];
  for (int i = 0; i < 4; i++) {
    arrd[i] = Direction(i);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= VISION_RANGE; j++) {
      Pos p(ppos.x + arrd[i].dx_ * j, ppos.y + arrd[i].dy_ * j);
      if (!InMap(p)) break;
      if (p == pos) return true;
      for (int l = 0; l <= 1; l++) {
        for (int k = 1; k <= VISION_RANGE; k++) {
          Pos p1(p.x + arrd[(i + 1 + 2 * l) % 4].dx_ * k,
                 p.y + arrd[(i + 1 + 2 * l) % 4].dy_ * k);
          if (p1 == pos) return true;
          if (!InMap(p1)) break;
          char c = GetMapChar(p1);
          if (c == WALL || c == CLOSED_DOOR) break;
        }
      }
      char c = GetMapChar(p);
      if (c == WALL || c == CLOSED_DOOR) break;
    }
  }
  return false;
}

bool Nethack::CanMove(Pos pos) {
  Map& map = map_vector_[player_->GetFloor()];
  if (!map.CanMove(pos)) return false;
  for (Monster& each : monsters_[player_->GetFloor()]) {
    if (each.GetPos() == pos) return false;
  }
  return true;
}

bool Nethack::CanMove(Pos pos, int floor) {
  Map& map = map_vector_[floor];
  if (!map.CanMove(pos)) return false;
  for (Monster& each : monsters_[floor]) {
    if (each.GetPos() == pos) return false;
  }
  return true;
}

bool Nethack::IsMonster(Pos pos) {
  for (Monster& each : monsters_[player_->GetFloor()]) {
    if (pos == each.GetPos()) {
      return true;
    }
  }
  return false;
}

bool Nethack::InMap(Pos pos) {
  return (pos.x > 0 && pos.y > 0 &&
          pos.x < map_vector_[player_->GetFloor()].GetHeight() &&
          pos.y < map_vector_[player_->GetFloor()].GetWidth());
}