#include "Chrono.h"

#include "DateV1.h"
#include "DateV2.h"

namespace {
constexpr int inc_year(int current_year) {
  return current_year == -1 ? 1 : ++current_year;
}

constexpr int dec_year(int current_year) {
  return current_year == 1 ? -1 : --current_year;
}
}  // namespace

namespace Chrono {
Date& default_date() {
  const date_v_2::DateV2 source;
  const Date::Month m{static_cast<Date::Month>(source.m)};
  static Date dd(source.y, m, source.d);
  return dd;
}

Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd) {
  if (!is_date(yy, mm, dd)) throw Invalid();
}

Date::Date()
    : y(default_date().year()),
      m(default_date().month()),
      d(default_date().day()) {}

void Date::add_day(int n) {
  const int month{static_cast<int>(m)};
  const date_v_2::DateV2 tmp(y, month, d);
  const date_v_2::DateV2 modified_date{date_v_2::add_day(tmp, n)};
  y = modified_date.y;
  m = static_cast<Date::Month>(modified_date.m);
  d = modified_date.d;
}

void Date::add_month(int n) {
  if (n == 0) return;
  const int count_sign{n > 0 ? -1 : 1};
  const int current_m{static_cast<int>(m)};
  m = static_cast<Date::Month>(std::abs((current_m + n * count_sign) % 12));
  const int left{(current_m + n * count_sign) / 12};
  if (left > 0) y = inc_year(y);
  if (left < 0) y = inc_year(y);
  add_month(left);
}

void Date::add_year(int n) {
  if (n > 0) y = inc_year(y), add_year(n - 1);
  if (n < 0) y = dec_year(y), add_year(n + 1);
}

bool is_date(int y, Date::Month m, int d) {
  const int month{static_cast<int>(m)};
  return date_v_1::is_date_valid(y, month, d);
}

bool leapyear(int y) { return date_v_1::is_leap_year(y); }

bool operator==(const Date& a, const Date& b) {
  return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
}

bool operator!=(const Date& a, const Date& b) { return !(a == b); }

std::ostream& operator<<(std::ostream& os, const Date& date) {
  const int month{static_cast<int>(date.month())};
  return os << date.day() << "." << month << "." << date.year();
}

std::istream& operator>>(std::istream& is, Date& date) {
  const char delimiter{'.'};
  int y, m, d;
  char d1, d2;
  is >> d >> d1 >> m >> d2 >> y;
  if (d1 != delimiter || d2 != delimiter) {
    is.clear(std::ios_base::failbit);
    return is;
  }

  date = Date(y, Date::Month(m), d);
  return is;
}

}  // namespace Chrono