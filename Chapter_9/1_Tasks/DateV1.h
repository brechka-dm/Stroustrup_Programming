#pragma once

#include <string>

/*
 * This file contains a definition of the DateV1 structure for working with the
 * date, as well as auxiliary functions.
 */

namespace date_v_1 {
struct DateV1 {
  int y;
  int m;
  int d;
};

// If the set y, m, d represents a valid description of the date, then dd is
// initialized with these values, otherwise dd remains unchanged.
void init_date(DateV1& dd, int y, int m, int d);

// Adds n days to dd, n can have a negative value.
void add_day(DateV1& dd, int n);

// Returns true if the set y, m, d represents a valid description of the date.
bool is_date_valid(int y, int m, int d);

bool is_leap_year(int y);

// Outputs the date in the format dd.mm.yyyy, with the value end added at the
// end of the string.
void print_date(const DateV1& dd, const std::string& end = "\n");
}  // namespace date_v_1