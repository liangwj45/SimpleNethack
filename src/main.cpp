// NethactMain.cpp
#include "NethackUI.hpp"

int main() {
  /*HANDLE  hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  for (int i_ = 15; i_ >= 0; i_--)
  {
  SetConsoleTextAttribute(hConsole, i_);
  cout << i_ << " what color is this?" << endl;
  }
  getchar();*/
  // system("mode con cols=118 lines=31");
  NethackUI nethack_ui;
  nethack_ui.StartUI();
}