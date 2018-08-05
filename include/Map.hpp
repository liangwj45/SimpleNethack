// Map.hpp
#ifndef _MAP_
#define _MAP_
#include <iostream>
#include <memory>
#include <vector>
#include "Item.hpp"
#include "Macro.hpp"
#include "Pos.hpp"
#include "Queue.hpp"
#include "Random.hpp"
#include "Room.hpp"
using std::cout;
using std::endl;
using std::vector;

class Map {
 public:
  Map();                  // default constructor
  Map(const Map& other);  // copy constructor
  ~Map();                 // destructor
  Map& operator=(const Map& other);

 public:
  int GetWidth() const;            // get width of the map
  int GetHeight() const;           // get height of the map
  char GetMapChar(Pos pos) const;  // get the char of the map at the position
  bool GetView(Pos pos) const;  // get whether the map of the position is viewed
  void PrintMap();              // print the whole map
  void ChangeMap(Pos pos, char c);  // to change the map of the position
  void ChangeView(Pos pos);         // to change the view of the position
  bool CanMove(Pos pos) const;      // determine whether can go to the position
  Pos FindSpace() const;            // to find a position that is floor_
  int ComputeDistance(Pos p1, Pos p2)
      const;  // to compute the distance from position A to position B
  // Pos  GetUpstair() const; // get upstair
  Pos GetDownstair() const;  // get downstair
  void SetUpStair(Pos pos);
  void SetNecklace();

 private:
  // funtion for constructing the map
  void SetPath(const Door& d1,
               const Door& d2);  // set path between the doors of rooms
  void OtherSet();               // for some more door and floor_
 private:
  char** map_;
  bool** view_;
  int width_;
  int height_;
  Pos upstair_, downstair_;
  vector<Room> room_vector_;
};

#endif  // !_MAP_
