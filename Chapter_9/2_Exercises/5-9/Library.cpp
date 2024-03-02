#include "Library.h"

#include <numeric>

std::vector<Patron>::iterator Library::checkPatron(int patronNumber) {
  return std::find_if(pPatrons.begin(), pPatrons.end(),
                      [patronNumber](const Patron& patron) {
                        return patron.getNumber() == patronNumber;
                      });
}

std::vector<Book>::iterator Library::checkBook(const std::string& isbn) {
  return std::find_if(pBooks.begin(), pBooks.end(), [&isbn](const Book& book) {
    return book.getIsbn() == isbn;
  });
}

void Library::addBook(const Book& book) { pBooks.push_back(book); }

void Library::addPatron(const Patron& patron) { pPatrons.push_back(patron); }

void Library::issueBook(const std::string& isbn, int patronNumber) {
  const auto booksIter = checkBook(isbn);
  if (booksIter == pBooks.end()) throw NoBook(isbn);

  const auto patronsIter = checkPatron(patronNumber);
  if (patronsIter == pPatrons.end()) throw NoPatron(patronNumber);

  if (!patronsIter->isPaid()) throw NoFee(patronNumber);

  pTransactions.push_back(
      Transaction{*booksIter, *patronsIter, Chrono::Date()});
}

void Library::returnBook(const std::string& isbn, int patronNumber) {
  const auto transactionsIter =
      std::find_if(pTransactions.begin(), pTransactions.end(),
                   [&](const Transaction& transaction) {
                     return transaction.patron.getNumber() == patronNumber &&
                            transaction.book.getIsbn() == isbn;
                   });
  if (transactionsIter != pTransactions.end()) {
    pTransactions.erase(transactionsIter);
  }
}

std::vector<std::string> Library::getBacklogs() const {
  return std::accumulate(
      pTransactions.begin(), pTransactions.end(), std::vector<std::string>{},
      [](std::vector<std::string> accumulator,
         const Transaction& transaction) {
        return (accumulator.push_back(transaction.patron.getName()),
                accumulator);
      });
}

std::vector<Book> Library::getPatronsBacklog(int patronNumber) const {
  return std::accumulate(
      pTransactions.begin(), pTransactions.end(), std::vector<Book>{},
      [patronNumber](auto accumulator, const Transaction& transaction) {
        if (transaction.patron.getNumber() == patronNumber)
          accumulator.push_back(transaction.book);
        return accumulator;
      });
}