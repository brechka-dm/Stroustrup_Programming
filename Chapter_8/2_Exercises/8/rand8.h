#pragma once

namespace {
    constexpr int z{ 2 };
    constexpr int k{ 7 };
    constexpr int e{ 16 };

    inline constexpr int power(int base, int exponent) {
        return (exponent == 0) ? 1 : (base * power(base, exponent - 1));
    }

    inline constexpr int a() { return power(z, k) + 1; }
    inline constexpr int m() { return power(z, e); }
}

inline constexpr int rand8(int n) {
    return n == 0 ? 0 : (a() * rand8(n - 1) + 1) % m();
}