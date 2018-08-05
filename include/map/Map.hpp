#ifndef _MAP_
#define _MAP_

#include <algorithm>
#include <queue>

#include "position/Direction.hpp"
#include "position/Position.hpp"

#include "utility/Utility.hpp"
#include "utility/defines.hpp"

namespace SimpleNethack {

#define MAX_MAP_HEIGHT 28
#define MAX_MAP_WIDTH 70
#define ROOM_WIDTH_MIN 10
#define ROOM_WIDTH_MAX 22
#define ROOM_HEIGHT_MIN 4
#define ROOM_HEIGHT_MAX 8
#define WALL '#'
#define FLOOR '.'
#define PATH '.'
#define CLOSED_DOOR '/'
#define OPEN_DOOR '`'
#define UPSTAIR '>'
#define DOWNSTAIR '<'
#define INF 999

class Map {
 public:
  /**
   * @brief Construct a new Map object
   * 1. CreateBasicMap()
   * 2. CreateRooms()
   * 3. SetWall()
   * 4. SetFloor()
   * 5. SetPaths()
   * 6. SetDownstair()
   * 7. OtherSet()
   *
   * @param pos position of player(and upstair)
   */
  Map(const Position& pos = Position(2, 2));

  /**
   * @brief Construct a new Map object
   *
   * @param other
   */
  Map(const Map& other);

  /**
   * @brief
   *
   * @param pos
   * @param c
   */
  void ChangeMap(const Position& pos, char c);

  /**
   * @brief Get the Map Char object
   *
   * @param pos
   * @return char
   */
  char GetMapChar(const Position& pos) const;

  /**
   * @brief find a position where the map char is FLOOR
   *
   * @return Position
   */
  Position FindSpace() const;

  /**
   * @brief compute the distance from position lhs to position rhs
   *
   * @param lhs
   * @param rhs
   * @return int the distance
   */
  int ComputeDistance(const Position& lhs, const Position& rhs) const;

  /**
   * @brief Set the Necklace object
   *
   */
  void SetNecklace();

  /**
   * @brief Print the whole map
   *
   */
  void PrintMap() const;

 private:
  /**
   * @brief
   *
   */
  struct Door : public Position {
    Door(int x = 0, int y = 0);
  };

  /**
   * @brief
   *
   */
  struct Room {
    /**
     * @brief Construct a new Room object
     *
     * @param ux
     * @param ly
     */
    Room(int ux, int ly);

    /**
     * @brief
     *
     * @param i
     * @return Door&
     */
    Door& operator[](int id);

    /**
     * @brief
     *
     * @return Position
     */
    Position FindSpace() const;

    /**
     * @brief Set the Door object
     *
     */
    void SetDoor();

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool InRoom(const Position& pos);

    int ux_, dx_, ly_, ry_;
    std::vector<Door> door_vector_;
  };

  /**
   * @brief Create a Basic Map object
   *
   */
  void CreateBasicMap();

  /**
   * @brief Create a Rooms object
   *
   * @param pos
   */
  int CreateRooms(const Position& pos);

  /**
   * @brief Set the Wall object
   *
   */
  void SetWall();

  /**
   * @brief Set the Floor object
   *
   */
  void SetFloor();

  /**
   * @brief Set the Paths object
   *
   */
  void SetPaths();

  /**
   * @brief Set the Downstair object
   *
   */
  void SetDownstair(const Position& pos, int upi);

  /**
   * @brief Set the Upstair object
   *
   */
  void SetUpstair(const Position& pos);

  /**
   * @brief Other set for doors and floor
   *
   */
  void OtherSet();

  /**
   * @brief Set path between the doors of rooms
   *
   * @param d1
   * @param d2
   */
  void SetPath(const Door& d1, const Door& d2);

 private:
  Position upstair_;
  Position downstair_;
  char map_[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
  std::vector<Room> room_vector_;
};
}  // namespace SimpleNethack
#endif