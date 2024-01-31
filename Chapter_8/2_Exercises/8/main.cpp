#include <cstdlib>
#include <ctime>
#include <iostream>

#include "rand.h"

using namespace std;

int main() {
  const long long seed{time(0)};
  srand(seed);
  ex8::set_seed(seed);

  constexpr int a{1};
  constexpr int b{10};
  constexpr int n{20};

  for (int i = 0; i < n; ++i) cout << ex8::rand_in_range(a, b) << " ";
  cout << endl;
  for (int i = 0; i < n; ++i) cout << a + rand() % (b - a) << " ";

  return 0;
}