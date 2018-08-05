// Macro.hpp
#ifndef _MACRO_
#define _MACRO_

#define CREATE_MONSTER_ROUND 20
#define MONSTER_INITIAL_NUMBER 10
#define ITEM_NUMBER 30
#define DOWNSTAIR_NUMBER 1

#define STATEX 4
#define STATEY 78

#define LEVEL_X STATEX
#define LEVEL_Y STATEY
#define EXP_X LEVEL_X + 1
#define EXP_Y LEVEL_Y
#define HP_X LEVEL_X + 2
#define HP_Y LEVEL_Y
#define MP_X LEVEL_X + 3
#define MP_Y LEVEL_Y
#define FLOOR_X LEVEL_X
#define FLOOR_Y LEVEL_Y + 15
#define ATK_X FLOOR_X + 1
#define ATK_Y FLOOR_Y
#define KILL_X FLOOR_X + 2
#define KILL_Y FLOOR_Y
#define MONSTER_X FLOOR_X + 3
#define MONSTER_Y FLOOR_Y
#define EVENT_X STATEX + 6
#define EVENT_Y STATEY
#define DIRECTION_X STATEX + 14
#define BEHAVIOR_X STATEX + 14
#define EVENT_NUMBER 5

#define VISION_RANGE 3

#define MAX_MAP_HEIGHT 28
#define MAX_MAP_WIDTH 70
#define ROOM_WIDTH_MIN 10
#define ROOM_MAX_WIDTH 22
#define ROOM_HEIGTH_MIN 4
#define ROOM_MAX_HEIGTH 8

#define MONSTER_COLOR 12
#define PLAYER_COLOR 14
#define LIGHT_COLOR 15

#define PLAYER '@'
#define WALL '#'
#define FLOOR '.'
#define PATH '.'
#define CLOSED_DOOR '/'
#define OPEN_DOOR '`'
#define UPSTAIR '>'
#define DOWNSTAIR '<'

#define INF 999

#endif // !_MACRO_
