// NethackUI.cpp
#include "NethackUI.hpp"

NethackUI::NethackUI() = default;

void NethackUI::StartUI() {
  GetName();
  StartGame();
}

void NethackUI::GetName() {
  // the base coordinate
  int x = 5;
  int y = 37;
  Pos::SetCursor(x + 21, y + 2);
  cout << "-* Press enter to continue *-";
  Pos::SetCursor(x, y);
  cout << ">> Welcome to Joker's Nethack, Hero!";
  Pos::SetCursor(x + 3, y);
  cout << ">> You are in the Dungeons now.";
  getchar();
  Pos::SetCursor(x + 6, y);
  cout << ">> Your mission is to dive into Floor Ten";
  getchar();
  Pos::SetCursor(x + 9, y);
  cout << ">> to get the precious necklace for the Queen.";
  getchar();
  Pos::SetCursor(x + 12, y);
  cout << ">> What's your name?";
  Pos::SetCursor(x + 21, y);
  cout << "                                 ";
  Pos::SetCursor(x + 15, y);
  cout << ">> ";
  char c;
  while ((c = getchar()) == '\n') {
    Pos::SetCursor(x + 15, y + 3);
  }
  std::cin >> name_;
  name_ = c + name_;
  Pos::SetCursor(x + 18, y);
  cout << ">> Good luck, " << name_ << "!";
  Sleep(1000);
  getchar();
}

void NethackUI::StartGame() {
  open_bag_ = false;
  win_ = false;
  round_count_ = 0;
  system("cls");
  // hide cursor
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursor_info;
  GetConsoleCursorInfo(handle, &cursor_info);  //��ȡ����̨�����Ϣ
  cursor_info.bVisible = false;                //���ؿ���̨���
  SetConsoleCursorInfo(handle, &cursor_info);  //���ÿ���̨���״̬
                                               // print a frame
  PrintEvent(" come to the Dungeons.");
  Pos::SetCursor(2, STATEY + 10);
  cout << "Nethack @_lwj";
  // Pos::SetCursor(1, STATEY - 3);
  // cout << "��";
  // for (int i = 1; i < 19; i++) {
  // 	cout << "--";
  // }
  // cout << "��";
  // for (int i = 0; i < 26; i++) {
  // 	Pos::SetCursor(i + 2, STATEY - 3);
  // 	cout << "��";
  // 	Pos::SetCursor(i + 2, STATEY + 35);
  // 	cout << "��";
  // }
  // Pos::SetCursor(28, STATEY - 3);
  // cout << "��";
  // for (int i = 1; i < 19; i++) {
  // 	cout << "--";
  // }
  // cout << "��";

  // print the illustration
  // Pos::SetCursor(DIRECTION_X, STATEY + 19);
  // cout << "Direction:";
  // Pos::SetCursor(DIRECTION_X + 2, STATEY + 21);
  // cout << "  ��";
  // Pos::SetCursor(DIRECTION_X + 3, STATEY + 21);
  // cout << "�IQWE�J";
  // Pos::SetCursor(DIRECTION_X + 4, STATEY + 21);
  // cout << "��ASD��";
  // Pos::SetCursor(DIRECTION_X + 5, STATEY + 21);
  // cout << "�LZ C�K";
  // Pos::SetCursor(DIRECTION_X + 6, STATEY + 21);
  // cout << "   �� ";
  Pos::SetCursor(BEHAVIOR_X, STATEY);
  cout << "Behavior:";
  Pos::SetCursor(BEHAVIOR_X + 1, STATEY);
  cout << "J  Pick up";
  Pos::SetCursor(BEHAVIOR_X + 2, STATEY);
  cout << "K  Attack";
  Pos::SetCursor(BEHAVIOR_X + 3, STATEY);
  cout << "L  Event/Bag";
  Pos::SetCursor(BEHAVIOR_X + 4, STATEY);
  cout << "U  Up/Down";
  Pos::SetCursor(BEHAVIOR_X + 5, STATEY);
  cout << "O  Open";
  Pos::SetCursor(BEHAVIOR_X + 6, STATEY);
  cout << "R  Reset";
  Pos::SetCursor(BEHAVIOR_X + 7, STATEY);
  cout << "H  Heal";
  Pos::SetCursor(BEHAVIOR_X + 8, STATEY);
  cout << "G  Goldenfinger";
  Pos::SetCursor(KILL_X, KILL_Y);
  cout << "   Kill: ";
  Pos::SetCursor(MONSTER_X, MONSTER_Y);
  cout << "Monster: ";
  GameLoop();
}

void NethackUI::GameLoop() {
  // create player
  player_ = nethack_.GetPlayer();
  nethack_.CleanMap();
  nethack_.Vision();
  nethack_.PrintMonster();
  PrintFloor();
  PrintLevel();
  PrintExp();
  PrintHp();
  PrintMp();
  PrintAtk();
  PrintMonsterCount();
  // getchar();
  // StartGame();
  bool action;
  char operation;
  while (operation = _getch()) {
    action = false;
    if (open_bag_) {
      int oper = operation - 48;
      if (oper > 0 && oper <= player_->BagSize()) {
        Item item = player_->GetBag()[oper - 1].first;
        action = player_->UseItem(oper - 1);
        if (action) {
          if (item.GetNum() < 3) {
            PrintEvent(string(" drank the ") + item.GetName() + '.');
          } else {
            stringstream ss;
            string s;
            ss << item.GetDatk();
            ss >> s;
            s = " equipped " + item.GetName() + ", ATK+" + s + '.';
            PrintEvent(s);
            PrintAtk();
          }
        } else
          PrintEvent(" did nothing.");
      }
    }
    if (!action) {
      switch (operation) {
        case 'w':
        case 'W':
          action = Move(Direction(0));
          break;
        case 'd':
        case 'D':
          action = Move(Direction(1));
          break;
        case 's':
        case 'S':
          action = Move(Direction(2));
          break;
        case 'a':
        case 'A':
          action = Move(Direction(3));
          break;
        case 'e':
        case 'E':
          action = Move(Direction(4));
          break;
        case 'c':
        case 'C':
          action = Move(Direction(5));
          break;
        case 'z':
        case 'Z':
          action = Move(Direction(6));
          break;
        case 'q':
        case 'Q':
          action = Move(Direction(7));
          break;
        case 'o':
        case 'O':
          action = OpenDoor();
          break;
        case 'k':
        case 'K':
          action = Attack();
          break;
        case 'h':
        case 'H':
          action = Heal();
          break;
        case 'r':
        case 'R':
          player_->Recover();
          action = true;
          break;
        case 'u':
        case 'U':
          action = ChangeStair();
          break;
        case 'j':
        case 'J':
          action = PickUp();
          break;
        case 'l':
        case 'L':
          if (!open_bag_)
            PrintBag();
          else
            PrintEvent();
          action = false;
          break;
        case 'g':
        case 'G':
          nethack_.Goldenfinger();
          action = true;
          break;
        default:
          action = false;
          break;
      }
    }
    if (action) {
      round_count_++;
      if (round_count_ % CREATE_MONSTER_ROUND == 0) {
        nethack_.CreateMonster();
        PrintMonsterCount();
      }
      nethack_.Vision();
      player_->Recover();
      nethack_.MonsterAction();
      PrintHp();
      PrintMp();
    }
    if (win_ || player_->GetHp() <= 0) break;
  }
  EndGame();
}

bool NethackUI::EndGame() {
  string event;
  event = win_ ? " fially got the Necklace!" : " was killed.";
  PrintEvent(event);
  string s;
  s.resize(35);
  Pos::SetCursor(13, STATEY);
  cout << s;
  Pos::SetCursor(14, STATEY);
  cout << s;
  Pos::SetCursor(15, STATEY);
  cout << s;
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, 12);
  Pos::SetCursor(14, STATEY);
  cout << (win_ ? "You win!" : "You lose!");
  Pos::SetCursor(15, STATEY);
  cout << "Restart? Y or N";
  SetConsoleTextAttribute(handle, 7);
  char c = _getch();
  while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
    c = _getch();
  }
  if (c == 'n' || c == 'N')
    return false;
  else {
    nethack_.InitialGame();
    event_log_.clear();
    kill_count_ = 0;
    round_count_ = 0;
    open_bag_ = false;
    win_ = false;
    StartGame();
    return true;
  }
}

void NethackUI::PrintEvent(string event) {
  event = name_ + event;
  event.resize(35);
  event_log_.push_back(event);
  PrintEvent();
}

void NethackUI::PrintEvent() {
  open_bag_ = false;
  Pos::SetCursor(EVENT_X, EVENT_Y);
  cout << "Event:";
  string s(35, ' ');
  for (int i = 0; i < EVENT_NUMBER; i++) {
    Pos::SetCursor(EVENT_X + i + 1, EVENT_Y);
    cout << s;
  }
  int size =
      event_log_.size() > EVENT_NUMBER ? EVENT_NUMBER : event_log_.size();
  for (int i = 0; i < size; i++) {
    Pos::SetCursor(EVENT_X + i + 1, EVENT_Y);
    cout << event_log_[event_log_.size() - i - 1];
  }
}

void NethackUI::PrintBag() {
  open_bag_ = true;
  Pos::SetCursor(EVENT_X, EVENT_Y);
  cout << "Bag:  ";
  string s(35, ' ');
  for (int i = 0; i < EVENT_NUMBER; i++) {
    Pos::SetCursor(EVENT_X + i + 1, EVENT_Y);
    cout << s;
  }
  vector<std::pair<Item, int>> bag = player_->GetBag();
  int num = EVENT_NUMBER;
  int x = EVENT_X;
  cout << std::setiosflags(std::ios::left);
  if (player_->IsWeaponed()) {
    Pos::SetCursor(x + 1, EVENT_Y);
    cout << std::setw(4) << '*' << std::setw(18)
         << player_->GetWeapon().GetName();
    num--;
    x++;
  }
  int size = bag.size() > num - 1 ? num - 1 : bag.size();
  for (int i = 0; i < size; i++) {
    Pos::SetCursor(x + i + 1, EVENT_Y);
    string item_string;
    cout << std::setw(4) << i + 1 << std::setw(18) << bag[i].first.GetName()
         << "*" << bag[i].second;
  }
  Pos::SetCursor(x + size + 1, EVENT_Y);
  cout << "(Press num to use)";
}

bool NethackUI::Move(Direction dir) {
  if (nethack_.move(dir)) {
    Pos::SetCursor(MONSTER_X + 1, MONSTER_Y);
    cout << "              ";
    return true;
  }
  return false;
}

bool NethackUI::OpenDoor() {
  if (nethack_.OpenDoor()) {
    PrintEvent(" opened a door.");
    return true;
  }
  return false;
}

bool NethackUI::Heal() {
  if (nethack_.Heal()) {
    PrintEvent(" healed, HP+15, MP-3.");
    return true;
  }
  return false;
}

bool NethackUI::ChangeStair() {
  char c = nethack_.GetMapChar(player_->GetPos());
  int floor = player_->GetFloor();
  if (floor == 9 && c == DOWNSTAIR) {
    PrintEvent(string(" couldn't go down any more."));
    return false;
  }
  if (nethack_.ChangeStair()) {
    stringstream ss;
    string s;
    ss << floor;
    ss >> s;
    s = " came to Floor " + s + '.';
    PrintEvent(s);
    PrintFloor();
    return true;
  }
  return false;
}

bool NethackUI::PickUp() {
  Pos ppos = player_->GetPos();
  char c = nethack_.GetMapChar(ppos);
  if (c == '&') {
    win_ = true;
    return false;
  }
  if (c != UPSTAIR && c != DOWNSTAIR && c != FLOOR && c != OPEN_DOOR) {
    player_->PickUp(c);
    nethack_.ChangeMap(player_->GetPos(), FLOOR);
    Item item(c);
    PrintEvent(string(" pick up a ") + item.GetName() + '.');
    return true;
  }
  return false;
}

bool NethackUI::Attack() {
  if (!nethack_.Attack()) return false;
  Monster& monster =
      nethack_.GetMonster(player_->GetPos() + player_->GetDirection());
  int hp = monster.GetHp();
  if (hp > 0) {
    // attacked monster
    Pos::SetCursor(MONSTER_X + 1, MONSTER_Y);
    cout << "HP of " << monster.GetSymbol() << ": " << hp << "  ";
  } else {
    // killed monster
    Pos::SetCursor(MONSTER_X + 1, MONSTER_Y);
    cout << "              ";
    PrintEvent(string(" killed the monster ") + monster.GetSymbol() + '.');
    nethack_.DeleteMonster(monster.GetPos());
    kill_count_++;
    PrintMonsterCount();
    // level_ up
    if (player_->Grow(2)) {
      PrintEvent(" level up! HP+5, MP+1, ATK+2.");
      PrintHp();
      PrintMp();
      PrintAtk();
      PrintLevel();
    }
    PrintExp();
  }
  return true;
}

void NethackUI::PrintLevel() {
  Pos::SetCursor(LEVEL_X, LEVEL_Y);
  cout << "LEVEL: " << player_->GetLevel() << "  ";
}

void NethackUI::PrintExp() {
  Pos::SetCursor(EXP_X, EXP_Y);
  cout << "  EXP: " << player_->GetExp() << "  ";
}

void NethackUI::PrintHp() {
  HANDLE honsole;
  honsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int color = player_->GetHp() < player_->GetMaxHp() ? 12 : 7;
  SetConsoleTextAttribute(honsole, color);
  Pos::SetCursor(HP_X, HP_Y);
  cout << "   HP: " << player_->GetHp() << "/" << player_->GetMaxHp() << "  ";
  SetConsoleTextAttribute(honsole, 7);
}

void NethackUI::PrintMp() {
  HANDLE honsole;
  honsole = GetStdHandle(STD_OUTPUT_HANDLE);
  int color = player_->GetMp() < player_->GetMaxMp() ? 9 : 7;
  SetConsoleTextAttribute(honsole, color);
  Pos::SetCursor(MP_X, MP_Y);
  cout << "   MP: " << player_->GetMp() << "/" << player_->GetMaxMp() << "  ";
  SetConsoleTextAttribute(honsole, 7);
}

void NethackUI::PrintAtk() {
  Pos::SetCursor(ATK_X, ATK_Y);
  cout << "    ATK: " << player_->GetAtk() << "  ";
}

void NethackUI::PrintFloor() {
  Pos::SetCursor(FLOOR_X, FLOOR_Y);
  cout << "  FLOOR: " << player_->GetFloor() + 1 << "  ";
}

void NethackUI::PrintMonsterCount() {
  Pos::SetCursor(KILL_X, KILL_Y + 9);
  cout << kill_count_;
  Pos::SetCursor(MONSTER_X, MONSTER_Y + 9);
  cout << nethack_.GetMonsterCount() << "  ";
}

/*
������
��  ��
������
*/