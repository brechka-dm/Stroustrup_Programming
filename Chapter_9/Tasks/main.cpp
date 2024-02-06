#include "DateV1.h"

int main(){
  date_v_1::DateV1 dd;
  date_v_1::init_date(dd, 2024, 02, 05);
  date_v_1::print_date(dd, " - 300d = ");
  date_v_1::add_day(dd, -300);
  date_v_1::print_date(dd);
}