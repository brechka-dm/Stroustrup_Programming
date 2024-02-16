#pragma once

#include <string>

#include "Chrono.h"

class Book {
  const std::string pIsbn;
  const std::string pAuthor;
  const Chrono::Date pRegisterDate;
  bool pIssued{false};

 public:
  class InvalidIsbn;
  class InvalidAuthor;
  
  Book(const std::string& isbn, const std::string& author,
       const Chrono::Date& registerDate);
  void setIssued(bool issued);
  const std::string& getIsbn() const { return pIsbn; }
  const std::string& getAuthor() const { return pAuthor; }
  const Chrono::Date& getRegisterDate() const { return pRegisterDate; }
  bool isIssued() const { return pIssued; }
};