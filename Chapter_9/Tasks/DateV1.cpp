#include "DateV1.h"

#include <iostream>

namespace {
constexpr bool is_february_day_correct(int y, int d) {
  return date_v_1::is_leap_year(y) ? d < 30 : d < 29;
}

constexpr bool is_minor_month(int m) {
  return m == 4 || m == 6 | m == 9 || m == 11;
}

constexpr bool is_day_correct(int y, int m, int d) {
  return m == 2              ? is_february_day_correct(y, d)
         : is_minor_month(m) ? d < 31
                             : d < 32;
}

constexpr int days_in_month(int m, int y) {
  if (m < 0 || y < 0) return 0;
  if (is_minor_month(m)) return 30;
  if (m == 2) return date_v_1::is_leap_year(y) ? 29 : 28;
  return 31;
}

constexpr int inc_year(int current_year) {
  return current_year == -1 ? 1 : ++current_year;
}

constexpr int dec_year(int current_year) {
  return current_year == 1 ? -1 : --current_year;
}

date_v_1::DateV1 inc_month(const date_v_1::DateV1& dd) {
  int current_m{dd.m};
  int current_y{dd.y};
  if (current_m < 12)
    ++current_m;
  else
    current_m = 1, current_y = inc_year(current_y);
  return date_v_1::DateV1{current_y, current_m, dd.d};
}

date_v_1::DateV1 dec_month(const date_v_1::DateV1& dd) {
  int current_m{dd.m};
  int current_y{dd.y};
  if (current_m > 1)
    --current_m;
  else
    current_m = 12, current_y = dec_year(current_y);
  return date_v_1::DateV1{current_y, current_m, dd.d};
}

void sub_day(date_v_1::DateV1& date, int n) {
  while (n != 0) {
    int days_sum{date.d + n};
    int days_in_current_month{days_in_month(date.m, date.y)};
    if (days_sum >= 0) {
      date.d = days_sum;
      return;
    }
    date.d = 0;
    date = dec_month(date);
    n = days_sum + days_in_month(date.m, date.y);
    if (n == 0) continue;
  }
}

}  // namespace

void date_v_1::init_date(DateV1& dd, int y, int m, int d) {
  if (is_date_valid(y, m, d)) dd = DateV1{y, m, d};
}
void date_v_1::add_day(DateV1& dd, int n) {
  while (n != 0) {
    int days_sum{dd.d + n};
    int days_in_current_month{days_in_month(dd.m, dd.y)};
    if (days_sum < 0) {
      dd.d = 0;
      dd = dec_month(dd);
      n = days_sum + days_in_month(dd.m, dd.y);
      if (n == 0) continue;
    } else {
      dd.d = days_sum % days_in_current_month;
      n = days_sum / days_in_current_month;
      if (n < 0) {
        dd = dec_month(dd);
        ++n;
        if (n == 0) continue;
      } else if (n > 0) {
        dd = inc_month(dd);
        --n;
        if (n == 0) continue;
      }
    }
  }
}

bool date_v_1::is_date_valid(int y, int m, int d) {
  if (d < 1 || d > 31) return false;
  if (m < 1 || m > 12) return false;
  switch (m) {
    case 2:
      if (d > 29) return false;
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      if (d > 30) return false;
      break;
  }
  if (!is_leap_year(y) && m == 2 && d > 28) return false;
  return true;
}

bool date_v_1::is_leap_year(int y) {
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

void date_v_1::print_date(const DateV1& dd, const std::string& end) {
  using namespace std;
  cout << dd.d << "." << dd.m << "." << dd.y << end;
}