#include "Book.h"

int main() {
  Book b("1-2-3-q", "B Straus", "C++",
         Chrono::Date(2013, Chrono::Date::Month::jul, 3), Book::Genre::Fiction);
  Book d("1-2-3-d", "B Straus", "C++",
         Chrono::Date(2013, Chrono::Date::Month::jul, 3),
         Book::Genre::Children);
  if (b != d) {
    std::cout << b << d;
  }
}