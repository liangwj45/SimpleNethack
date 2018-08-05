#include "handle/Nethack.hpp"

namespace SimpleNethack {

shared_ptr<Nethack> Nethack::instance_ = nullptr;

std::shared_ptr<Nethack> Nethack::GetInstance() {
  if (!instance_) {
    instance_.reset(new Nethack);
  }
  return instance_;
}

void Nethack::Destroy() {
  MapManager::GetInstance()->clear();
  ViewManager::GetInstance()->clear();
  MonsterManager::GetInstance()->clear();
  instance_ = nullptr;
}

Nethack::Nethack() { Initial(); }

Nethack::~Nethack() {}

void Nethack::Initial() {
  floor_ = 0;
  see_monster_ = false;

  player_ = Player::GetInstance();
  const Position& pos = player_->GetPosition();
  map_ = MapManager::GetInstance()->GetMap(floor_, pos);
  view_ = ViewManager::GetInstance()->GetView(floor_, pos);
  monsters_ = MonsterManager::GetInstance()->GetMonsters(floor_);

  monsters_->clear();
  for (int i = 0; i < MONSTER_INITIAL_NUMBER; i++) {
    CreateMonster();
  }

  PrintMap();
  UpdateView();
  // map_->PrintMap();
}

void Nethack::CreateMonster() {
  Position ppos = player_->GetPosition();
  Position mpos = map_->FindSpace();
  while (mpos == ppos || IsMonster(mpos)) {
    mpos = map_->FindSpace();
  }
  Monster monster(mpos, floor_ / 3 + 3, floor_ + 16);
  monsters_->push_back(std::move(monster));
}

void Nethack::UpdateView() {
  // HideVision();
  PrintVision();
  PrintCenter();
  UpdateMonster();
}

void Nethack::HideVision() {
  const Position& pos = player_->GetPosition();
  int x = pos.x - VISION_RANGE - 1;
  int y = pos.y - VISION_RANGE - 1;
  for (int i = x; i < x + VISION_RANGE * 2 + 2; i++) {
    for (int j = 0; j < 2; j++) {
      Position p(i, y + (VISION_RANGE * 2 + 2) * j);
      if (InMap(p)) {
        char c = (*view_)(p) ? GetMapChar(p) : ' ';
        Print(p.x, p.y, 7, c);
      }
    }
  }
  for (int i = y; i < y + VISION_RANGE * 2 + 2; i++) {
    for (int j = 0; j < 2; j++) {
      Position p(x + (VISION_RANGE * 2 + 2) * j, i);
      if (InMap(p)) {
        char c = (*view_)(p) ? GetMapChar(p) : ' ';
        Print(p.x, p.y, 7, c);
      }
    }
  }
}

void Nethack::PrintCenter() {
  const Position& pos = player_->GetPosition();
  Print(pos.x, pos.y, PLAYER_COLOR, PLAYER);
}

void Nethack::PrintVision() {
  const Position& pos = player_->GetPosition();
  int range = VISION_RANGE + 1;
  for (int i = -range; i <= range; i++) {
    for (int j = -range; j <= range; j++) {
      Position p(pos.x + i, pos.y + j);
      if (CanSee(p)) {
        (*view_)[p] = true;
        Print(p.x, p.y, LIGHT_COLOR, GetMapChar(p));
      } else if (InMap(p)) {
        char c = (*view_)(p) ? GetMapChar(p) : ' ';
        Print(p.x, p.y, 7, c);
      }
    }
  }
}

void Nethack::UpdateMonster() {
  for (Monster& monster : *monsters_) {
    Position mpos = monster.GetPosition();
    if (CanSee(mpos)) {
      Print(mpos.x, mpos.y, MONSTER_COLOR, monster.GetSymbol());
    }
  }
}

void Nethack::MonsterAction() {
  const Position& ppos = player_->GetPosition();
  for (Monster& each : *monsters_) {
    MonsterRecover(each);
    const Position& mpos = each.GetPosition();
    if (CanAttack(mpos)) {
      AttackPlayer(each);
      continue;
    }
    if (ComputeXY(ppos, mpos) <= 20) {
      GetCloser(each);
      continue;
    }
    RandomMove(each);
  }
}

void Nethack::MonsterRecover(Monster& monster) { monster.Recover(); }

void Nethack::AttackPlayer(const Monster& monster) {
  const Position& ppos = player_->GetPosition();
  const Position& mpos = monster.GetPosition();
  player_->Hurt(monster.GetAtk());
  // Print(mpos.x, mpos.y, MONSTER_COLOR, monster.GetSymbol());
  Print(ppos.x, ppos.y, 12, PLAYER);
  Sleep(50);
  Print(ppos.x, ppos.y, PLAYER_COLOR, PLAYER);
}

void Nethack::GetCloser(Monster& monster) {
  const Position& pos = monster.GetPosition();
  Direction direction = GetDirection(pos);
  if (CanMove(pos + direction)) {
    monster.Move(direction);
  }
}

void Nethack::RandomMove(Monster& monster) {
  const Position& pos = monster.GetPosition();
  const Direction& direction = RandomDirection(pos);
  if (CanMove(pos + direction)) {
    monster.Move(direction);
  }
}

bool Nethack::Nethack::Move(const Direction& dir) {
  const Position& pos = player_->GetPosition();
  direction_ = dir;
  if (CanMove(pos + dir)) {
    player_->Move(dir);
    return true;
  } else {
    return false;
  }
}

bool Nethack::Rest() {
  player_->Recover();
  player_->Recover();
  return true;
}

bool Nethack::Heal() {
  int hp = player_->GetHp();
  int max_hp = player_->GetMaxHp();
  int mp = player_->GetMp();
  if (hp == max_hp || mp < 3) {
    return false;
  }
  player_->Heal();
  return true;
}

bool Nethack::Pick(Item& item) {
  char c = map_->GetMapChar(player_->GetPosition());
  if (!Item::IsItem(c)) {
    return false;
  }
  item = Item(c);
  return player_->PickUp(item);
}

bool Nethack::Attack(bool& kill_signal) {
  const Position& ppos = player_->GetPosition();
  if (IsMonster(ppos + direction_)) {
    Monster& monster = GetMonster(ppos + direction_);
    monster.Hurt(player_->GetAtk());
    const Position& mpos = monster.GetPosition();
    Print(mpos.x, mpos.y, LIGHT_COLOR, monster.GetSymbol());
    Sleep(50);
    Print(mpos.x, mpos.y, MONSTER_COLOR, monster.GetSymbol());
    return true;
  }
  return false;
}

bool Nethack::OpenDoor() {
  const Position& pos = player_->GetPosition();
  Position door_pos = pos + direction_;
  if (InMap(door_pos) && GetMapChar(door_pos) == CLOSED_DOOR) {
    map_->ChangeMap(door_pos, OPEN_DOOR);
    return true;
  }
  return false;
}

bool Nethack::ChangeStair(int& floor) {
  char c = GetMapChar(this->player_->GetPosition());
  if ((c == UPSTAIR && floor_ == 0) || (c == DOWNSTAIR && floor_ == 9)) {
    return false;
  }
  CleanMap();

  floor = floor_ += (c == UPSTAIR ? 1 : -1);
  map_ = MapManager::GetInstance()->GetMap(floor_);
  view_ = ViewManager::GetInstance()->GetView(floor_);
  monsters_ = MonsterManager::GetInstance()->GetMonsters(floor_);
  for (int i = 0; i < MONSTER_INITIAL_NUMBER + floor; i++) {
    CreateMonster();
  }

  PrintMap();
  UpdateView();
  return true;
}

bool Nethack::UseItem(int id, Item& item) {
  auto bag = player_->GetBag()->item_list_;
  if (bag.size() <= id) {
    return false;
  }
  item = bag[id].first;
  player_->UseItem(id);
}

bool Nethack::SeeMonster() {
  see_monster_ = !see_monster_;
  return true;
}

bool Nethack::IsMonster(const Position& pos) {
  for (const Monster& each : *monsters_) {
    if (pos == each.GetPosition()) {
      return true;
    }
  }
  return false;
}

bool Nethack::CanAttack(const Position& mpos) {
  const Position& ppos = player_->GetPosition();
  return abs(ppos.x - mpos.x) <= 1 && abs(ppos.y - mpos.y) <= 1;
}

Direction Nethack::GetDirection(const Position& mpos) {
  Direction d(0);
  Position ppos = player_->GetPosition();
  Position pos;
  int min_i = 0;
  int min_xy = INF;
  int min_dis = INF;
  int i = 8;
  while (i--) {
    pos = mpos + --d;
    if (CanMove(pos)) {
      int dis = map_->ComputeDistance(pos, ppos);
      int xy = ComputeXY(pos, ppos);
      if (dis < min_dis || (dis == min_dis && xy <= min_xy)) {
        min_dis = dis;
        min_xy = xy;
        min_i = i;
      }
    }
  }
  return Direction(min_i);
}

Direction Nethack::RandomDirection(const Position& pos) {
  int t = 8;
  Direction d(rand(0, 7));
  while (t-- && !CanMove(pos + ++d))
    ;
  return d;
}

Monster& Nethack::GetMonster(const Position& pos) {
  for (Monster& each : *monsters_) {
    if (each.GetPosition() == pos) {
      return each;
    }
  }
  // TO: exception
}

bool Nethack::CanSee(const Position& pos) {
  Position ppos = player_->GetPosition();
  int x = ppos.x;
  int y = ppos.y;
  int range = VISION_RANGE;
  if (!InMap(pos) || abs(x - pos.x) > range || abs(y - pos.y) > range) {
    return false;
  }
  Direction arrd[4];
  for (int i = 0; i < 4; i++) {
    arrd[i] = Direction(i);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= range; j++) {
      Position p(x + arrd[i].GetDx() * j, y + arrd[i].GetDy() * j);
      if (!InMap(p)) break;
      if (p == pos) return true;
      for (int l = 0; l <= 1; l++) {
        for (int k = 1; k <= range; k++) {
          Position p1(p.x + arrd[(i + 1 + 2 * l) % 4].GetDx() * k,
                      p.y + arrd[(i + 1 + 2 * l) % 4].GetDy() * k);
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

bool Nethack::CanMove(const Position& pos) {
  char c = map_->GetMapChar(pos);
  if (c == WALL || c == CLOSED_DOOR || c == ' ') {
    return false;
  }
  for (Monster& each : *monsters_) {
    if (each.GetPosition() == pos) {
      return false;
    }
  }
  return true;
}

inline bool Nethack::InMap(const Position& pos) {
  return (pos.x > 0 && pos.y > 0 && pos.x < MAX_MAP_HEIGHT &&
          pos.y < MAX_MAP_WIDTH);
}

inline char Nethack::GetMapChar(const Position& pos) {
  return map_->GetMapChar(pos);
}

void Nethack::CleanMap() {
  string s(MAX_MAP_HEIGHT, ' ');
  for (int i = 0; i < MAX_MAP_HEIGHT; ++i) {
    Print(i, 0, 7, s);
  }
}

void Nethack::PrintMap() {
  for (int i = 0; i < MAX_MAP_HEIGHT; i++) {
    for (int j = 0; j < MAX_MAP_WIDTH; j++) {
      Position pos(i, j);
      char c = (*view_)(pos) ? map_->GetMapChar(pos) : ' ';
      Print(i, j, 7, c);
    }
  }
}

}  // namespace SimpleNethack