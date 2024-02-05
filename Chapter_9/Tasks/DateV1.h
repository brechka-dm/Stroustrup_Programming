#pragma once

#include <string>

namespace date_v_1 {
struct DateV1 {
  int y;
  int m;
  int d;
};

void init_date(DateV1& dd, int y, int m, int d);
void add_day(DateV1& dd, int n);
bool is_date_valid(int y, int m, int d);
bool is_leap_year(int y);

void print_date(const DateV1& dd, const std::string& end = "\n");
}  // namespace date_v_1