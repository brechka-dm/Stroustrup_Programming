#include "Book.h"

Book::Book(const std::string& isbn, const std::string& author,
           const Chrono::Date& registerDate)
    : pIsbn{isbn}, pAuthor{author}, pRegisterDate{registerDate} {
        
    }