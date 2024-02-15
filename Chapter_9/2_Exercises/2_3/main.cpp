#include "NamePairs.h"

int main() {
  NamePairs obj;
  obj.readNames();
  obj.readAges();
  obj.print();
  obj.sort();
  obj.print();
}