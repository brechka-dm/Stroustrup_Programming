#include "DateV1.h"

namespace {
constexpr bool is_february_day_correct(int y, int d) {
  return date_v_1::is_leap_year(y) ? d < 30 : d < 29;
}

constexpr bool is_minor_month(int m) {
  return m == 4 || m == 6 | m == 9 || m == 11;
}

constexpr bool is_day_correct(int y, int m, int d) {
  return m == 2              
    ? is_february_day_correct(y, d)
        : is_minor_month(m) ? d < 31
        : d < 32;
}

}  // namespace

void date_v_1::init_day(DateV1& dd, int y, int m, int d) {
  if (is_date_valid(y, m, d)) dd = DateV1{y, m, d};
}
void date_v_1::add_day(DateV1& dd, int n) {
  int d{dd.d + n};
  if (d < 1) {
  }  // do one;
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