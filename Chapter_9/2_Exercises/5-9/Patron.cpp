#include "Patron.h"

#include <regex>

Patron::Patron(const std::string& name, int number)
    : pName{name}, pNumber{number} {
  std::smatch matches;

  // Use regexp to check string format.
  if (!std::regex_match(pName, matches, std::regex("([a-zA-Z]+\\s*)+")))
    throw InvalidName();
  // Throw if number <=0.
  if (pNumber <= 0) throw InvalidNumber();
}

void Patron::setFee(float fee) { pFee = fee; }

void Patron::setPaid(bool paid) { pPaid = paid; }