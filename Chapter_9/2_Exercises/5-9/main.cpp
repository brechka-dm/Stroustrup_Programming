#include "Library.h"

struct BookData {
  const std::string caption;
  const std::string isbn;
  const std::string author;
  const Book::Genre genre;
  const Chrono::Date registerDate;
};

struct PatronData {
  const std::string name;
  const int number;
};

void maybeAddBook(Library& library, const BookData& bookData) {
  try {
    const Book book{bookData.isbn, bookData.author, bookData.caption,
                    bookData.registerDate, bookData.genre};
    library.addBook(book);
  } catch (const Book::InvalidIsbn&) {
    std::cerr << "ISBN \"" << bookData.isbn
              << "\" is invalid. Unable to create book" << std::endl;
  } catch (const Book::InvalidAuthor&) {
    std::cerr << "Author name \"" << bookData.author
              << "\" is invalid. Unable to create book" << std::endl;
  }
}

void maybeAddPatron(Library& library, const PatronData& patronData) {
  try {
    const Patron patron{patronData.name, patronData.number};
    library.addPatron(patron);
  } catch (const Patron::InvalidName&) {
    std::cerr << "Name \"" << patronData.name
              << "\" is invalid. Unable to create patron." << std::endl;
  } catch (const Patron::InvalidNumber&) {
    std::cerr << "Number \"" << patronData.number
              << "\" is invalid. Unable to create patron." << std::endl;
  }
}

int main() {
  Library library;

  maybeAddBook(
      library,
      BookData{"Programming. Principles and Practice Using C++", "987-2-1234-5",
               "Bjarne Stroustrup", Book::Genre::Fiction,
               Chrono::Date(2011, Chrono::Date::Month::jan, 1)});

  // Invalid ISBN.
  maybeAddBook(
      library,
      BookData{"Programming. Principles and Practice Using C++",
               "987-2-1234-5-7", "Bjarne Stroustrup", Book::Genre::Fiction,
               Chrono::Date(2011, Chrono::Date::Month::jan, 1)});

  // Invalid Author.
  maybeAddBook(library,
               BookData{"Programming. Principles and Practice Using C++",
                        "987-2-1234-5", "42", Book::Genre::Fiction,
                        Chrono::Date(2011, Chrono::Date::Month::jan, 1)});

  maybeAddPatron(library, PatronData{"John Dow", 1});

  // Invalid name.
  maybeAddPatron(library, PatronData{"42", 2});

  // Invalid number.
  maybeAddPatron(library, PatronData{"John Dow", 0});
}