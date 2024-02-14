#include "Chrono.h"

#include <ctime>
#include <iomanip>

#include "DateV1.h"
#include "DateV2.h"

namespace {
constexpr int inc_year(int current_year) {
  return current_year == -1 ? 1 : ++current_year;
}

constexpr int dec_year(int current_year) {
  return current_year == 1 ? -1 : --current_year;
}

std::string day_to_string(Chrono::Day d) {
  switch (d) {
    case Chrono::Day::sunday:
      return "sunday";
    case Chrono::Day::monday:
      return "monday";
    case Chrono::Day::tusday:
      return "tusday";
    case Chrono::Day::wensday:
      return "wensday";
    case Chrono::Day::thursday:
      return "thursday";
    case Chrono::Day::friday:
      return "friday";
    case Chrono::Day::saturday:
      return "saturday";
  }
  return "unknown";
}
}  // namespace

namespace Chrono {
Date& default_date() {
  const date_v_2::DateV2 source;
  const Date::Month m{static_cast<Date::Month>(source.m)};
  static Date dd(source.y, m, source.d);
  return dd;
}

Date::Date()
    : y(default_date().year()),
      m(default_date().month()),
      d(default_date().day()) {}

Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd) {
  if (!is_date(yy, mm, dd)) throw Invalid();
}

Date::Date(const Date& other) : y(other.y), m(other.m), d(other.d) {}

void Date::add_day(int n) {
  const int month{static_cast<int>(m)};
  const date_v_2::DateV2 tmp(y, month, d);
  const date_v_2::DateV2 modified_date{date_v_2::add_day(tmp, n)};
  y = modified_date.y;
  m = static_cast<Date::Month>(modified_date.m);
  d = modified_date.d;
}

void Date::add_month(int n) {
  const int current_month{static_cast<int>(m) - 1};
  if (n >= 0) {
    const int new_month{(current_month + n) % 12 + 1};
    const int years{(current_month + n) / 12};
    m = Month(new_month);
    add_year(years);
  }
  else{
    
  }
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
  using namespace std;
  return os << setw(2) << setfill('0') << date.day() << "." << setw(2)
            << setfill('0') << month << "." << date.year();
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

Day day_of_week(const Date& date) {
  int month = static_cast<int>(date.month());
  int year = date.year();
  int day = date.day();
  if (month < 3) {
    month += 12;
    year--;
  }

  int k = year % 100;
  int j = year / 100;

  int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

  // Значение h будет от 0 (суббота) до 6 (пятница).
  // Преобразуем его к виду, где 0 - воскресенье, 1 - понедельник, и т.д.
  return Day((h + 6) % 7);
}

Date next_sunday(const Date& date) {
  const int current_day{static_cast<Day>(day_of_week(date))};
  Date new_date = date;
  new_date.add_day(7 - current_day);
  return new_date;
}

Day next_weekday(const Date& date) {
  const int current_day{static_cast<Day>(day_of_week(date))};
  return Day((current_day + 1) % 7);
}

std::ostream& operator<<(std::ostream& os, Day d) {
  return os << day_to_string(d);
}
}  // namespace Chrono