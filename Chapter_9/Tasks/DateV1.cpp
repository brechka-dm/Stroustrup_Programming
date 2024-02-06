#include "DateV1.h"

#include <iomanip>
#include <iostream>

namespace {
constexpr bool is_february_day_correct(int y, int d) {
  return date_v_1::is_leap_year(y) ? d < 30 : d < 29;
}

// Returns true if m is equal to the number of the month that has 30 days.
constexpr bool is_minor_month(int m) {
  return m == 4 || m == 6 | m == 9 || m == 11;
}

// Returns true if d does not exceed the allowed number of days in month m of
// year y.
constexpr bool is_day_correct(int y, int m, int d) {
  return m == 2              ? is_february_day_correct(y, d)
         : is_minor_month(m) ? d < 31
                             : d < 32;
}

// Returns the number of days in month m of year y.
constexpr int days_in_month(int m, int y) {
  if (m < 0 || y < 0) return 0;
  if (is_minor_month(m)) return 30;
  if (m == 2) return date_v_1::is_leap_year(y) ? 29 : 28;
  return 31;
}

// Increases current_year by 1, bypassing the value 0.
constexpr int inc_year(int current_year) {
  return current_year == -1 ? 1 : ++current_year;
}

// Decreases current_year by 1, bypassing the value 0.
constexpr int dec_year(int current_year) {
  return current_year == 1 ? -1 : --current_year;
}

// Increases the value of the month number in dd by 1, given the year boundary
// crossing (possibly increasing the year).
date_v_1::DateV1 inc_month(const date_v_1::DateV1& dd) {
  int current_m{dd.m};
  int current_y{dd.y};
  if (current_m < 12)
    ++current_m;
  else
    current_m = 1, current_y = inc_year(current_y);
  return date_v_1::DateV1{current_y, current_m, dd.d};
}

// Decreases the value of the month number in dd by 1, given the year boundary
// crossing (possibly decreasing the year).
date_v_1::DateV1 dec_month(const date_v_1::DateV1& dd) {
  int current_m{dd.m};
  int current_y{dd.y};
  if (current_m > 1)
    --current_m;
  else
    current_m = 12, current_y = dec_year(current_y);
  return date_v_1::DateV1{current_y, current_m, dd.d};
}

// Subtracts n days from dd if n is negative.
void sub_days(date_v_1::DateV1& date, int n) {
  while (n <= 0) {
    int days_sum{date.d + n};
    if (days_sum >= 0) {
      date.d = days_sum;
      return;
    }
    date = dec_month(date);
    date.d = days_in_month(date.m, date.y);
    n = days_sum;
  }
}

// Adds n days to dd if n is positive.
void add_days(date_v_1::DateV1& date, int n) {
  while (n >= 0) {
    int days_sum{date.d + n};
    int days_in_current_month{days_in_month(date.m, date.y)};
    if (days_sum <= days_in_current_month) {
      date.d = days_sum;
      return;
    }
    date = inc_month(date);
    date.d = 0;
    n = days_sum - days_in_current_month;
  }
}
}  // namespace

void date_v_1::init_date(DateV1& dd, int y, int m, int d) {
  if (is_date_valid(y, m, d)) dd = DateV1{y, m, d};
}
void date_v_1::add_day(DateV1& dd, int n) {
  return n > 0 ? add_days(dd, n) : sub_days(dd, n);
}

bool date_v_1::is_date_valid(int y, int m, int d) {
  if (y == 0) return false;
  if (m < 1 || m > 12) return false;
  if (d < 1 || !is_day_correct(y, m, d)) return false;
  return true;
}

bool date_v_1::is_leap_year(int y) {
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

void date_v_1::print_date(const DateV1& dd, const std::string& end) {
  using namespace std;
  cout << setw(2) << setfill('0') << dd.d << "." << setw(2) << setfill('0')
       << dd.m << "." << dd.y << end;
}