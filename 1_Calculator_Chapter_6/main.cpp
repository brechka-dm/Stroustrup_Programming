#include <iostream>

using namespace std;

int main() {
  cout << "Input the expression (+ and - allowed): ";
  int l_val = 0;
  int r_val;
  char operation;
  int result;
  cin >> l_val >> operation >> r_val;

  if (operation == '+')
    result = l_val + r_val;
  else if (operation == '-')
    result = l_val - r_val;

  cout << "Result:" << result << '\n';
  return 0;
}