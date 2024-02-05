#include <iostream>

#include "DateV1.h"

using namespace std;

int main(){
  date_v_1::DateV1 dd;
  date_v_1::init_date(dd, 2024, 02, 05);
  date_v_1::print_date(dd);
  date_v_1::add_day(dd, -7);
  date_v_1::print_date(dd);
}