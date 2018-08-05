#include "handle/GameUI.hpp"

namespace SimpleNethack {
NethackUI::NethackUI() {}

void NethackUI::SetUp() {
  Prepare();
  do {
    Initital();
    GameLoop();
    CleanUp();
    Ending();
  } while (!over_singal_);
}

void NethackUI::Prepare() {
  Preface();
  BasicPrint();
}

void NethackUI::Initital() {
  floor_ = 0;

  kill_count_ = 0;
  round_count_ = 0;
  monster_count_ = 0;

  open_bag_ = false;
  stop_singal_ = false;
  action_ = false;

  int x = rand(0, 2) * 9 + 2 + rand(1, 6);
  int y = rand(0, 2) * 23 + 2 + rand(1, 20);
  Position pos(x, y);
  player_ = Player::GetInstance(pos);
  nethack_ = Nethack::GetInstance();

  event_log_.clear();
  UpdateData();
}

void NethackUI::GameLoop() {
  PrintEvent(string("welcome to my Nethack."));
  while (!stop_singal_) {
    try {
      operation_ = GetOperation();
      ExecuteOperation();
      if (action_) {
        player_->Recover();
        ++round_count_;
        UpdateData();
        UpdateView();
        EnemyRound();
      }
    } catch (const char* e) {
      PrintEvent(string(e));
    }
  }
  PrintEvent(tostring("Hp: ", player_->GetHp()));
}

char NethackUI::GetOperation() {
  set<char> operations({'w', 'W', 's', 'S', 'a', 'A', 'd', 'D', 'q', 'Q', 'e',
                        'E', 'z', 'Z', 'c', 'C', 'j', 'J', 'k', 'K', 'l', 'L',
                        'h', 'H', 'r', 'R', 'u', 'U', 'o', 'O', 'g', 'G'});
  char c = _getch();
  if (operations.find(c) == operations.end() && !isdigit(c))
    throw "invalid operation";
  if (isdigit(c) && !open_bag_) throw "Bag is not open";
  return c;
}

void NethackUI::ExecuteOperation() {
  if (open_bag_ && isdigit(operation_)) {
    UseItem();
    return;
  }
  switch (operation_) {
    case 'r':
    case 'R':
      Rest();
      break;
    case 'h':
    case 'H':
      Heal();
      break;
    case 'j':
    case 'J':
      Pick();
      break;
    case 'k':
    case 'K':
      Attack();
      break;
    case 'o':
    case 'O':
      OpenDoor();
      break;
    case 'u':
    case 'U':
      ChangeStair();
      break;
    case 'g':
    case 'G':
      Gold();
      break;
    case 'l':
    case 'L':
      OpenBag();
      break;
    default:
      Move();
      break;
  }
}

void NethackUI::Move() {
  switch (operation_) {
    case 'w':
    case 'W':
      action_ = nethack_->Move(Direction(0));
      break;
    case 'd':
    case 'D':
      action_ = nethack_->Move(Direction(1));
      break;
    case 's':
    case 'S':
      action_ = nethack_->Move(Direction(2));
      break;
    case 'a':
    case 'A':
      action_ = nethack_->Move(Direction(3));
      break;
    case 'e':
    case 'E':
      action_ = nethack_->Move(Direction(4));
      break;
    case 'c':
    case 'C':
      action_ = nethack_->Move(Direction(5));
      break;
    case 'z':
    case 'Z':
      action_ = nethack_->Move(Direction(6));
      break;
    case 'q':
    case 'Q':
      action_ = nethack_->Move(Direction(7));
      break;
    default:
      action_ = false;
      break;
  }

  // TO:
  // if (nethack_.move(dir)) {
  //   Print(MONSTER_X + 1, MONSTER_Y, "              ");
  //   return true;
  // }
}

void NethackUI::Rest() { action_ = nethack_->Rest(); }

void NethackUI::Heal() {
  int hp = player_->GetHp();
  int mp = player_->GetMp();
  action_ = nethack_->Heal();
  if (action_) {
    PrintEvent(tostring("healed, HP+", player_->GetHp() - hp, ", MP-3."));
  }
}

void NethackUI::Pick() {
  Item item;
  action_ = nethack_->Pick(item);
  if (action_) {
    const string& item_name = item.GetName();
    PrintEvent(string("pick up a ") + item_name + '.');
    if (item_name == "necklace") {
      stop_singal_ = true;
    }
  }
}

void NethackUI::Attack() {
  int level = player_->GetLevel();
  bool kill_signal;
  action_ = nethack_->Attack(kill_signal);
  if (action_ && kill_signal) {
    ++kill_count_;
    --monster_count_;
    PrintEvent(string("kill a monster."));
    if (level < player_->GetLevel()) {
      PrintEvent(string("level up! HP+5, MP+1, ATK+2."));
    }
  }

  // TO: show monster data
  // Monster& monster =
  //     nethack_.GetMonster(player_->GetPos() + player_->GetDirection());
  // int hp = monster.GetHp();
  // Print(MONSTER_X + 1, MONSTER_Y,
  //       tostring("HP of ", monster.GetSymbol(), ": ", hp, "  "));
}

void NethackUI::OpenDoor() {
  action_ = nethack_->OpenDoor();
  if (action_) {
    PrintEvent(string("open a door."));
  }
}

void NethackUI::ChangeStair() {
  int floor = floor_;
  action_ = nethack_->ChangeStair(floor_);
  if (action_) {
    if (floor < floor_) {
      PrintEvent(string("go upstair."));
    } else {
      PrintEvent(string("go downstair."));
    }
  }
}

void NethackUI::UseItem() {
  Item item;
  int atk = player_->GetAtk();
  int hp = player_->GetHp();
  int mp = player_->GetMp();
  action_ = nethack_->UseItem(operation_ - '0', item);
  if (action_) {
    string item_name = item.GetName();
    string item_type = item.GetType();
    if (item_type == "Potion") {
      string message = tostring("drank the ", item.GetName());
      int dhp = player_->GetHp() - hp;
      int dmp = player_->GetMp() - mp;
      if (dhp > 0) {
        message += tostring(", HP+", dhp);
      }
      if (dmp > 0) {
        message += tostring(", MP+", dmp);
      }
      message.push_back('.');
      PrintEvent(std::move(message));
      return;
    }
    if (item_type == "Weapon") {
      int datk = player_->GetAtk() - atk;
      string message = tostring("used ", item.GetName());
      if (datk != 0) {
        message += tostring(", ATK", (datk > 0 ? '+' : '-'), abs(datk));
      }
      message.push_back('.');
      PrintEvent(std::move(message));
      return;
    }
  } else {
    PrintEvent(string("can't use this item."));
  }
}

void NethackUI::Gold() { action_ = nethack_->SeeMonster(); }

void NethackUI::OpenBag() {
  open_bag_ = !open_bag_;
  if (open_bag_) {
    PrintBag();
  } else {
    PrintEvent();
  }
  action_ = false;
}

void NethackUI::UpdateView() { nethack_->UpdateView(); }

void NethackUI::EnemyRound() {
  nethack_->MonsterAction();
  if (player_->GetHp() <= 0) {
    stop_singal_ = true;
  }
  nethack_->UpdateMonster();
}

// TO: clean up
void NethackUI::CleanUp() {
  Player::Destroy();
  Nethack::Destroy();
}

void NethackUI::Ending() {
  bool win = player_->GetHp() > 0 ? true : false;
  string event = win ? " fially got the Necklace!" : " was killed.";
  PrintEvent(std::move(event));

  string blank(35, ' ');
  Print(13, STATEY, 7, blank);
  Print(14, STATEY, 7, blank);
  Print(15, STATEY, 7, blank);
  Print(14, STATEY, 12, (win ? "You win!" : "You lose!"));
  Print(15, STATEY, 12, "Restart? Y or N");

  char restart = _getch();
  while (restart != 'Y' && restart != 'y' && restart != 'N' && restart != 'n') {
    restart = _getch();
  }
  if (restart == 'n' || restart == 'N') {
    over_singal_ = true;
  } else {
    over_singal_ = false;
  }
}

void NethackUI::Preface() {
  system("cls");
  Print(27, 39, 7, "-* Press enter to continue *-");
  Print(5, 37, 7, ">> Welcome to Joker's Nethack, Hero!");
  Print(8, 37, 7, ">> You are in the Dungeons now.");
  getchar();
  Print(11, 37, 7, ">> Your mission is to dive into Floor Ten");
  getchar();
  Print(14, 37, 7, ">> to get the precious necklace for the Queen.");
  getchar();
  Print(17, 37, 7, ">> What's your name?");
  Print(26, 37, 7, "                                 ");
  Print(20, 37, 7, ">> ");
  cin >> name_;
  Print(23, 37, 7, ">> Good luck, ", name_, "!");
  Sleep(1000);
}

void NethackUI::BasicPrint() {
  system("cls");

  // hide cusor
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursor_info;
  GetConsoleCursorInfo(handle, &cursor_info);  //获取控制台光标信息
  cursor_info.bVisible = false;                //隐藏控制台光标
  SetConsoleCursorInfo(handle, &cursor_info);  //设置控制台光标状态

  // print frame
  string s1(37, '_');
  string s2(37, ' ');
  string s3;
  s3 = "|" + s1 + "|";
  s2 = "|" + s2 + "|";
  s1 = " " + s1 + " ";
  Print(0, 75, 7, s1);
  for (int i = 1; i < 28; i++) {
    Print(i, 75, 7, s2);
  }
  Print(28, 75, 7, s3);

  Print(2, 88, 7, "Nethack @_lwj");

  Print(18, 97, 7, "Direction:");
  Print(20, 99, 7, "  *");
  Print(21, 99, 7, "*QWE*");
  Print(22, 99, 7, "*ASD*");
  Print(23, 99, 7, "*Z C*");
  Print(24, 99, 7, "  * ");

  Print(18, 78, 7, "Behavior:");
  Print(19, 78, 7, "J  Pick up");
  Print(20, 78, 7, "K  Attack");
  Print(21, 78, 7, "L  Event/Bag");
  Print(22, 78, 7, "U  Up/Down");
  Print(23, 78, 7, "O  Open");
  Print(24, 78, 7, "R  Reset");
  Print(25, 78, 7, "H  Heal");
  Print(26, 78, 7, "G  Goldenfinger");

  Print(4, 78, 7, "LEVEL: ");
  Print(5, 78, 7, "  EXP: ");
  Print(6, 78, 7, "   HP: ");
  Print(7, 78, 7, "   MP: ");

  Print(4, 95, 7, "  Floor: ");
  Print(5, 95, 7, "    ATK: ");
  Print(6, 95, 7, "   Kill: ");
  Print(7, 95, 7, "Monster: ");
}

void NethackUI::UpdateData() {
  Print(4, 85, 7, player_->GetLevel(), "  ");
  Print(5, 85, 7, player_->GetExp(), "  ");
  Print(6, 85, 7, player_->GetHp(), "  ");
  Print(7, 85, 7, player_->GetMp(), "  ");

  Print(4, 105, 7, floor_ + 1, "  ");
  Print(5, 105, 7, player_->GetAtk(), "  ");
  Print(6, 105, 7, kill_count_, "  ");
  Print(7, 105, 7, monster_count_, "  ");
}

void NethackUI::PrintEvent(string&& message) {
  message = name_ + ", " + message;
  message.resize(35);
  event_log_.push_back(std::move(message));
  PrintEvent();
}

void NethackUI::PrintEvent() {
  int num = EVENT_NUMBER;
  int x = EVENT_X;
  int y = EVENT_Y;

  Print(x, y, 7, "Event:");

  string blank(35, ' ');
  for (int i = 0; i < num; i++) {
    Print(x + i + 1, y, 7, blank);
  }

  int size = event_log_.size() < num ? event_log_.size() : num;
  for (int i = 0; i < size; i++) {
    Print(x + i + 1, y, 7, event_log_[event_log_.size() - i - 1]);
  }
}

void NethackUI::PrintBag() {
  int num = EVENT_NUMBER;
  int x = EVENT_X;
  int y = EVENT_Y;

  Print(x, y, 7, "Bag:  ");
  string blank(35, ' ');
  for (int i = 0; i < num; i++) {
    Print(x + i + 1, y, 7, blank);
  }

  auto bag = player_->GetBag()->item_list_;

  cout << std::setiosflags(std::ios::left);

  if (player_->IsWeaponed()) {
    string weapon_name = player_->GetWeapon()->GetName();
    weapon_name.resize(18);
    Print(x + 1, y, 7, "   *", weapon_name);
    num--;
    x++;
  }

  int size = bag.size() > num - 1 ? num - 1 : bag.size();
  for (int i = 0; i < size; i++) {
    string s1 = std::to_string(i + 1);
    s1.resize(4);
    string s2 = bag[i].first.GetName();
    s2.resize(18);
    Print(x + i + 1, y, 7, s1, s2, "*", bag[i].second);
  }
  Print(x + size + 1, y, 7, "(Press num to use)");
}

}  // namespace SimpleNethack