#pragma once

#include "Book.h"
#include "Chrono.h"
#include "Patron.h"

struct Transaction {
  Book book;
  Patron patron;
  Chrono::Date date;
};