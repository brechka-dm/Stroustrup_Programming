#include "DateV2.h"

#include <ctime>
#include <iomanip>

#include "DateV1.h"

namespace {
// Converts DateV1 to DateV2.
date_v_2::DateV2 v1_to_v2(const date_v_1::DateV1 v1) {
  return date_v_2::DateV2(v1.y, v1.m, v1.d);
}

// Converts DateV2 to DateV1.
date_v_1::DateV1 v2_to_v1(const date_v_2::DateV2 v2) {
  date_v_1::DateV1 v1;
  date_v_1::init_date(v1, v2.y, v2.m, v2.d);
  return v1;
}
}  // namespace

date_v_2::DateV2::DateV2() {
  // Use time to get current time (see
  // https://en.cppreference.com/w/cpp/chrono/c/time).
  time_t now = time(0);
  // Use tm strucure to represent date/time (see
  // https://en.cppreference.com/w/cpp/chrono/c/tm).
  struct tm time_struct;
  // Use localtime_s to extract tm strucure (see
  // https://en.cppreference.com/w/c/chrono/localtime).
  localtime_s(&time_struct, &now);
  // The initial value of the year in tm is 1900, to get the current year, we
  // need to add 1900 to the value in tm.
  this->y = time_struct.tm_year + 1900;
  // The numbering of months in tm starts from 0, to get the current month,
  // we need to add 1 to the value in tm.
  this->m = time_struct.tm_mon + 1;
  this->d = time_struct.tm_mday;
}

date_v_2::DateV2::DateV2(int y, int m, int d) {
  // Use date_v_1::is_date_valid to validate input data.
  if (date_v_1::is_date_valid(y, m, d))
    // Use this as a pointer to the current object.
    this->y = y, this->m = m, this->d = d;
  else
    DateV2();
}

date_v_2::DateV2 date_v_2::add_day(const date_v_2::DateV2& date, int days) {
  date_v_1::DateV1 v1{v2_to_v1(date)};
  // Use date_v_1::add_day to change date.
  date_v_1::add_day(v1, days);
  return v1_to_v2(v1);
}

std::ostream& operator<<(std::ostream& stream, const date_v_2::DateV2& date) {
  using namespace std;
  return stream << setw(2) << setfill('0') << date.d << "." << setw(2)
                << setfill('0') << date.m << "." << date.y;
}