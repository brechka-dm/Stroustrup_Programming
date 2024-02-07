#pragma once

#include <iostream>

/*
 * This file contains a definition of the DateV2 structure for working with the
 * date, as well as auxiliary functions.
 */

namespace date_v_2 {
struct DateV2 {
  // The constructor checks the validity of the entered data, if the data is
  // valid, compiles the date from it, otherwise the date is initialized with
  // "today" value.
  DateV2(int y, int m, int d);
  int y;
  int m;
  int d;
};

// Adds days to date, returns a new instance of the structure, the original date
// is unchanged.
DateV2 add_day(const DateV2& date, int days);
}  // namespace date_v_2

// Overloads the date output operation.
std::ostream& operator<<(std::ostream& stream, const date_v_2::DateV2& date);