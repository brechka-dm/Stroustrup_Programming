#include "Chrono.h"
#include "DateV1.h"
#include "DateV2.h"

int main() {
  std::cout << "V1: " << std::endl;
  date_v_1::DateV1 dd;
  date_v_1::init_date(dd, 2024, 02, 05);
  date_v_1::print_date(dd, " - 300d = ");
  date_v_1::add_day(dd, -300);
  date_v_1::print_date(dd);

  std::cout << "V2: " << std::endl;
  date_v_2::DateV2 dd2{2024, 02, 07};
  std::cout << dd2 << " - 300d = ";
  std::cout << date_v_2::add_day(dd2, -300);

  std::cout << std::endl << "V3: " << std::endl;
  Chrono::Date dd3{2024, Chrono::Date::Month(02), 07};
  std::cout << dd3 << " - 300d = ";
  dd3.add_day(-300);
  std::cout << dd3 << std::endl;
  std::cout << "Day of week: " << Chrono::day_of_week(dd3) << std::endl;
  std::cout << "Next sunday: " << Chrono::next_sunday(dd3) << std::endl;
  std::cout << "Next week day: " << Chrono::next_weekday(dd3) << std::endl;
  dd3.add_month(-20);
  std::cout << "-9m: " << dd3 << std::endl;
  dd3.add_year(-13);
  std::cout << "+13y: " << dd3 << std::endl;
}