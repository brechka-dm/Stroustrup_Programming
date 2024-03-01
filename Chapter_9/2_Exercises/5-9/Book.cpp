#include "Book.h"

#include <regex>
#include <unordered_map>

namespace {
// This map is used to represent Book::Genre as string.
const std::unordered_map<Book::Genre, std::string> bookGenre{
    {Book::Genre::Biography, "Biography"},
    {Book::Genre::Children, "Children's literature"},
    {Book::Genre::Fiction, "Fiction"},
    {Book::Genre::Periodical, "Pereodical"},
    {Book::Genre::Prose, "Prose"}};
}  // anonymous namespace

Book::Book(const std::string& isbn, const std::string& author,
           const std::string& caption, const Chrono::Date& registerDate,
           Genre genre)
    : pIsbn{isbn},
      pAuthor{author},
      pCaption{caption},
      pRegisterDate{registerDate},
      pGenre{genre} {
  // Use regexp to check string format. See Chapter 23.6 - 23.9.
  std::smatch matches;

  // (One ore more digit and one "-") repeat 3 times, and one or more
  // alphanumeric.
  if (!std::regex_match(pIsbn, matches, std::regex("(\\d+-){3}\\w+")))
    throw InvalidIsbn();

  // (One or more lowercase or capital letters and one unnecessary space symbol)
  // repeat one ore more times.
  if (!std::regex_match(pAuthor, matches, std::regex("([a-zA-Z]+\\s?)+")))
    throw InvalidAuthor();
}

void Book::setIssued(bool issued) { pIssued = issued; }

bool operator==(const Book& book1, const Book& book2) {
  // Compare ISBNs.
  return book1.getIsbn() == book2.getIsbn();
}

bool operator!=(const Book& book1, const Book& book2) {
  return !(book1 == book2);
}

std::ostream& operator<<(std::ostream& stream, const Book& book) {
  stream << "Caption: \"" << book.getCaption() << "\"\n"
         << "Author: " << book.getAuthor() << "\n"
         << "ISBN: " << book.getIsbn() << "\n";

  // Add genre string representation if genre is found in bookGenre.
  const auto genreIter = bookGenre.find(book.getGenre());
  if (genreIter != bookGenre.end()) {
    stream << "Genre: \"" << genreIter->second << "\"\n";
  }
  return stream;
}