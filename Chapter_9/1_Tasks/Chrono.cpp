#include "Chrono.h"

#include <ctime>
#include <iomanip>

#include "DateV1.h"
#include "DateV2.h"
#include "Utils.h"

namespace {
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
  // Should never happen.
  return "unknown";
}
}  // namespace

namespace Chrono {
// Default date is today.
Date& default_date() {
  // DateV2 is initialized with today's date by default.
  const date_v_2::DateV2 source;
  // Convert source.m to Date::Month.
  const Date::Month m {Date::Month(source.m)};
  // Create Chrono::Date initialized by today's date.
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
  // Convert month to int.
  const int month{static_cast<int>(m)};
  const date_v_2::DateV2 tmp(y, month, d);
  // Use date_v_2::add_day to perform calculations.
  const date_v_2::DateV2 modified_date{date_v_2::add_day(tmp, n)};
  // Convert results to data members.  
  y = modified_date.y;
  m = static_cast<Date::Month>(modified_date.m);
  d = modified_date.d;
}

void Date::add_month(int n) {
  int current_month{static_cast<int>(m) - 1};
  if (n >= 0) {
    const int new_month{(current_month + n) % 12 + 1};
    const int years{(current_month + n) / 12};
    m = Month(new_month);
    add_year(years);
  } else {
    const int years{(current_month + n) / 12 - 1};
    const int new_month{12 + (current_month + n) % 12};
    m = Month(new_month + 1);
    add_year(years);
  }
}

// Use recursion.
void Date::add_year(int n) {
  if (n > 0) y = Utils::inc_year(y), add_year(n - 1);
  if (n < 0) y = Utils::dec_year(y), add_year(n + 1);
}

bool is_date(int y, Date::Month m, int d) {
  const int month{static_cast<int>(m)};
  // Use date_v_1::is_date_valid to check date.
  return date_v_1::is_date_valid(y, month, d);
}

// Use date_v_1::is_leap_year to check year.
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

// Use Zeller's congruence to calc date
// See https://en.wikipedia.org/wiki/Zeller%27s_congruence
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

  // The value of h will be from 0 (Saturday) to 6 (Friday).
  // Convert it to a form where 0 is Sunday, 1 is Monday, etc.
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