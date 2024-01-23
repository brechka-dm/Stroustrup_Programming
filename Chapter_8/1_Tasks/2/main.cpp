#include <iostream>

/*
 * This program is solution of Task 2 from Chapter 8.
 */

void swap_v(int a, int b) {
  int temp;
  temp = a, a = b;
  b = temp;

  std::cout << "Internal: " << a << " " << b << std::endl;
}

void swap_r(int& a, int& b) {
  int temp;
  temp = a, a = b;
  b = temp;
}

// this function will not compile becouse of constant references.
// void swap_cr(const int& a, const int& b)
//{
//    int temp; temp = a, a=b; b=temp;
//}

int main() {
  // swap_v will not swap external variables because copies of values are passed
  // to the function.
  std::cout << "swap_v" << std::endl;
  int x = 7;
  int y = 9;
  swap_v(x, y);
  swap_v(7, 9);
  std::cout << "External: " << x << " " << y << std::endl;
  const int cx = 7;
  const int cy = 9;
  swap_v(cx, cy);
  swap_v(7.7, 9.9);
  std::cout << "External: " << cx << " " << cy << std::endl;
  double dx = 7.7;
  double dy = 9.9;
  swap_v(dx, dy);
  std::cout << "External: " << dx << " " << dy << std::endl;
  swap_v(dx, dy);
  std::cout << "External: " << dx << " " << dy << std::endl;

  std::cout << "swap_r" << std::endl;
  int x2 = 7;
  int y2 = 9;
  swap_r(x2, y2);
  // swap_r(7, 9); // will not compile because 7 and 9 are r-value.
  std::cout << "External: " << x2 << " " << y2 << std::endl;
  const int cx2 = 7;
  const int cy2 = 9;
  // swap_r(cx2, cy2); // will not compile because cx2 and cy2 are constants.
  // swap_r(7.7, 9.9); // will not compile because 7.7 and 9.9 are r-value.
  std::cout << "External: " << cx2 << " " << cy2 << std::endl;
  double dx2 = 7.7;
  double dy2 = 9.9;
  // swap_r(dx2, dy2); // will not compile because int& cannot be initialized by
  // double.
  std::cout << "External: " << dx2 << " " << dy2 << std::endl;

  return 0;
}