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
}