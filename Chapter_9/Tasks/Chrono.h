#pragma once

#include <iostream>

namespace Chrono {
class Date {
 public:
  enum Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

  class Invalid {};
  Date();
  Date(int yy, Month mm, int dd);
  Date(const Date& other);

  int day() const { return d; }
  Month month() const { return m; }
  int year() const { return y; }

  void add_day(int n);
  void add_month(int n);
  void add_year(int n);

 private:
  int y;
  Month m;
  int d;
};

bool is_date(int y, Date::Month m, int d);
bool leapyear(int y);
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
std::ostream& operator<<(std::ostream& os, const Date& date);
std::istream& operator>>(std::istream& is, Date& date);

enum Day { sunday = 0, monday, tusday, wensday, thursday, friday, saturday };
Day day_of_week(const Date& date);
Date next_sunday(const Date& date);
Day next_weekday(const Date& date);
std::ostream& operator<<(std::ostream& os, Day d);
}  // namespace Chrono