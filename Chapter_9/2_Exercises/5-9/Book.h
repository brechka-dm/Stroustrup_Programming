#pragma once

#include <iostream>
#include <string>

#include "Chrono.h"

/*
 * This class implements tasks 5, 6 and 7. 
 * Class uses Chrono::Date from Tasks to store registration date.
 */
class Book {
 public:
  // Added in task 7.
  enum Genre { Fiction = 0, Prose, Periodical, Biography, Children };

  // This classes are used as exception if wrong constructor parameters are set.
  class InvalidIsbn {};
  class InvalidAuthor {};

  Book(const std::string& isbn, const std::string& author,
       const std::string& caption, const Chrono::Date& registerDate, Genre genre);
  void setIssued(bool issued);
  const std::string& getIsbn() const { return pIsbn; }
  const std::string& getAuthor() const { return pAuthor; }
  const std::string& getCaption() const { return pCaption; }
  const Chrono::Date& getRegisterDate() const { return pRegisterDate; }

  // Added in task 7.
  Genre getGenre() const { return pGenre; }
  bool isIssued() const { return pIssued; }

 private:
  std::string pIsbn;
  std::string pAuthor;
  std::string pCaption;
  Chrono::Date pRegisterDate;
  
  // Added in task 7.
  Genre pGenre;
  bool pIssued{false};
};

// Next overloaded operators added in task 6.
bool operator==(const Book& book1, const Book& book2);
bool operator!=(const Book& book1, const Book& book2);
std::ostream& operator<<(std::ostream& stream, const Book& book);
