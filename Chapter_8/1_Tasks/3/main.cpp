#include <iostream>

/*
 * This program is solution of Task 3 from Chapter 8.
 */

namespace X {
int var;
void print() { std::cout << var << std::endl; }
}

namespace Y {
int var;
void print() { std::cout << var << std::endl; }
}

namespace Z {
int var;
void print() { std::cout << var << std::endl; }
}

int main() {
  X::var = 7;
  X::print();
  
  using namespace Y;
  var = 9;
  print();
  {
    using Z::print;
    using Z::var;
    var = 11;
    print();
  }
  print();
  X::print();
}