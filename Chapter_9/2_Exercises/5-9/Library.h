#pragma once

#include <vector>

#include "Transaction.h"

class Library {
  std::vector<Book> pBooks;
  std::vector<Patron> pPatrons;
  std::vector<Transaction> pTransactions;

  std::vector<Patron>::iterator checkPatron(int patronNumber);
  std::vector<Book>::iterator checkBook(const std::string& isbn);

 public:
  struct NoBook {
    std::string isbn;
  };
  struct NoPatron {
    int patronNumber{};
  };
  struct NoFee {
    int patronNumber{};
  };

  void addBook(const Book& book);
  void addPatron(const Patron& patron);
  void issueBook(const std::string& isbn, int patronNumber);
  void returnBook(const std::string& isbn, int patronNumber);
  std::vector<std::string> getBacklogs() const;
  std::vector<Book> getPatronsBacklog(int patronNumber) const;
};