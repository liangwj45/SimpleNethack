// Nethack.hpp
#ifndef _NETHACK_
#define _NETHACK_

#include <memory>
#include <vector>
#include <list>
#include <conio.h>
#include <string>
#include <functional>
#include "Map.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Macro.hpp"
using std::vector;
using std::list;
using std::string;

class Nethack {
public:
	Nethack();
	void InitialGame();
	void PrintMonster();
	void Vision();
	void ChangeMap(Pos pos, char c);
	int GetMonsterCount();
	Monster& GetMonster(Pos pos);
	std::shared_ptr<Player> GetPlayer();

	// player
	bool move(Direction dir);
	bool Attack();
	bool Heal();
	bool OpenDoor();
	bool ChangeStair();
	void Goldenfinger();

	// monster
public:
	void MonsterAction();
	void CreateMonster();
private:
	void MonsterAttack(Monster& monster);
	void MonsterMove(Monster& monster);
	Direction FindPath(Pos pos);
	Direction RandomDirection(Pos pos, std::function<bool(const Pos pos)> filter);
	bool CanAttackPlayer(Pos pos);
public:
	void DeleteMonster(Pos pos);

	// Map
	void HideMonster();
	char GetMapChar(Pos pos);
	void UpdateMap(Pos pos, int color, char c);
	void CleanMap();
	void PrintMap();
	bool CanSee(Pos pos);
	bool CanMove(Pos pos);
	bool CanMove(Pos pos, int floor);
	bool IsMonster(Pos pos);
	bool InMap(Pos pos);

private:
	bool see_monster_;
	vector<Map> map_vector_;
	std::shared_ptr<Player> player_;
	vector<list<Monster>> monsters_;
};

#endif // !_NETHACK_