#ifndef _ITEM_
#define _ITEM_

#include "utility/defines.hpp"

namespace SimpleNethack {
class Item {
 public:
  /**
   * @brief Construct a new Item object
   *
   * @param i
   */
  Item(int i = 2);

  /**
   * @brief Construct a new Item object
   *
   * @param c
   */
  Item(char c);

  /**
   * @brief
   *
   * @param other
   * @return true
   * @return false
   */
  bool operator==(const Item& other) const;

  /**
   * @brief Get the Num object
   *
   * @return int
   */
  int GetNum() const;

  /**
   * @brief Get the Symbol object
   *
   * @return char
   */
  char GetSymbol() const;

  /**
   * @brief Get the Datk object
   *
   * @return int
   */
  int GetDatk() const;

  /**
   * @brief Get the Name object
   *
   * @return std::string
   */
  string GetName() const;

  /**
   * @brief Get the Type object
   *
   * @return string
   */
  string GetType() const;

  /**
   * @brief
   *
   * @param c
   * @return true
   * @return false
   */
  static bool IsItem(char c);

 private:
  int id_;
  static vector<char> symbol_;
  static vector<int> atk_;
  static vector<string> name_;
  static vector<string> type_;
};
}  // namespace SimpleNethack
#endif