#include "rand.h"

namespace {
// The values of the numbers are taken from the article
// https://habr.com/ru/articles/499490/
constexpr unsigned long a{1103515245};
constexpr unsigned long c{12345};
constexpr unsigned long m{32768};  // 2^15
constexpr unsigned long n{65536};  // 2^16

static unsigned long int next = 1;
}  // namespace

unsigned long maxrand() { return m - 1; }

void ex8::set_seed(unsigned long int seed) { next = seed; }

int ex8::randint() {
  next = next * a + c;
  return static_cast<int>((next / n) % m);
}

int ex8::rand_in_range(int a, int b) { return a + randint() % (b - a); }