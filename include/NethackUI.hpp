// NethackUI 
#ifndef _NETHACKUI_
#define _NETHACKUI_
#include <iomanip>
#include <string>
#include <sstream>
#include "Nethack.hpp"
#include "Pos.hpp"
#include "Macro.hpp"
using std::string;
using std::stringstream;

class NethackUI {
public:
	NethackUI();
	void StartUI();
private:
	void GetName();
	void StartGame();
	void GameLoop();
	bool EndGame();
	void PrintEvent(string s);
	void PrintEvent();
	void PrintBag();
	bool Move(Direction dir);
	bool OpenDoor();
	bool Attack();
	bool Heal();
	bool ChangeStair();
	bool PickUp();
	void PrintLevel();
	void PrintExp();
	void PrintHp();
	void PrintMp(); 
	void PrintAtk(); 
	void PrintMonsterCount();
	void PrintFloor();

private:
	Nethack nethack_;
	string name_;
	vector<string> event_log_;
	std::shared_ptr<Player> player_;
	int kill_count_;
	int round_count_;
	bool open_bag_;
	bool win_;
};

#endif // !_NETHACKUI_
