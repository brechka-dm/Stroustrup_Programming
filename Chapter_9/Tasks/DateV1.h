#pragma once

namespace date_v_1 {
struct DateV1 {
  int y;
  int m;
  int d;
};

void init_day(DateV1& dd, int y, int m, int d);
void add_day(DateV1& dd, int n);
bool is_date_valid(int y, int m, int d);
bool is_leap_year(int y);
}  // namespace date_v_1