#ifndef _MYUTILITY_
#define _MYUTILITY_

#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "position/Position.hpp"

namespace SimpleNethack {

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Set the font color
 *
 * @param color color of the font
 */
void SetColor(int color);

/**
 * @brief Set the Cursor of console
 *
 * @param x
 * @param y
 */
void SetCursor(int x, int y);

/**
 * @brief Set the Cursor of console
 *
 * @param pos
 */
void SetCursor(const Position pos);

/**
 * @brief convert the type of the parameter to string
 *
 * @tparam paraType
 * @param para
 * @return string
 */
template <typename paraType>
string tostring(const paraType& para) {
  return string() + para;
}

string tostring(const int& para);

/**
 * @brief merge the parameters into a string
 *
 * @tparam paraType
 * @tparam Args
 * @param t
 * @param args
 * @return string
 */
template <typename paraType, typename... Args>
string tostring(const paraType& para, const Args&... args) {
  string result;
  result += tostring(para);
  result += tostring(args...);
  return result;
}

/**
 * @brief do some printing
 *
 * @tparam Args
 * @param x
 * @param y
 * @param color
 * @param args
 */
template <typename... Args>
void Print(int x, int y, int color, const Args&... args) {
  SetCursor(x, y);
  SetColor(color);
  cout << tostring(args...);
  SetColor(7);
}

/**
 * @brief get a random int
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int rand(int lhs, int rhs);

/**
 * @brief compute the distance between two position
 *
 * @param lhs
 * @param rhs
 * @return int
 */
int ComputeXY(const Position& lhs, const Position& rhs);
}  // namespace SimpleNethack

#endif