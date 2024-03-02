#pragma once

#include <string>

/*
 * This class implements task 8.
 */
class Patron {
 public:
  
  // Tis classes are used as an exceptions if wrong constructor parameters are set.
  class InvalidName {};
  class InvalidNumber {};

  Patron(const std::string& name, int number);
  void setFee(float fee);
  void setPaid(bool paid);
  const std::string& getName() const { return pName; }
  int getNumber() const { return pNumber; }
  float getFee() const { return pFee; }
  bool isPaid() const { return pPaid; }

 private:
  std::string pName;
  float pFee{};
  int pNumber{};
  bool pPaid{false};
};