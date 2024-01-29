#include <iostream>

#include "rand8.h"

using namespace std;

int main() {
    for (int i{ 0 }; i < 34; ++i) {
        cout << rand8(i) << " ";
    }
    return 0;
}